#include <esp_lge.h>
#include <LittleFS.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <lge_memory.h>
#include <cpu.h>
#include <display.h>
#include <sound.h>
#include <io.h>
#include <rom.h>

TFT_eSPI tft = TFT_eSPI();
Coos<4, 0> coos;

uint8_t i2c_adress;
uint8_t thiskey;
uint8_t serial_used = 0;
char c;
Ticker timer;
int delay_rtttl = 50;
uint16_t cadr_count = 0;
unsigned long timeF, timeR;
uint16_t timeCpu = 0, timeGpu = 0, timeSpr = 0, cpuOPS = 0, cpuOPSD = 0;
uint8_t fps, fileIsLoad;
uint8_t timeForRedraw = 48;
uint8_t fixed_res_bit = 8;
volatile uint16_t timers[8];

uint16_t palette[16] __attribute__((aligned));
uint16_t sprtpalette[16] __attribute__((aligned));

uint16_t bgr_to_rgb(uint16_t c)
{
  return ((c & 0x001f) << 11) + ((c & 0xf800) >> 11) + (c & 0x07e0);
}

unsigned char hexToByte(char h)
{
  if (h < 48)
    return 48;
  if (h >= 48 && h <= 57)
    h = map(h, 48, 57, 0, 9);
  else if (h >= 65 && h <= 70)
    h = map(h, 65, 70, 10, 15);
  else if (h >= 97 && h <= 102)
    h = map(h, 97, 102, 10, 15);
  return h;
}

void loadFromSerial()
{
  char c = 0;
  unsigned char n;
  int16_t j = 0;
  for (int16_t i = 0; i < RAM_SIZE; i++)
    writeMem(i, 0);
  while (c != '.')
  {
    if (Serial.available())
    {
      c = Serial.read();
      Serial.print(c);
      if (c == '$')
      {
        n = 48;
        while (n > 15)
        {
          c = Serial.read();
          n = hexToByte(c);
        }
        Serial.print(c);
        writeMem(j, n << 4);
        n = 48;
        while (n > 15)
        {
          c = Serial.read();
          n = hexToByte(c);
        }
        Serial.print(c);
        writeMem(j, readMem(j) + n);
        j++;
      }
    }
  }
  Serial.println(F("load "));
  Serial.print(j);
  Serial.println(F(" byte"));
  Serial.print(F("free heap "));
  Serial.println(system_get_free_heap_size());
  cpuInit();
}

void viewEEPROM()
{
  for (int16_t i = 0; i < EEPROM_SIZE; i++)
  {
    if (i % 32 == 0)
      Serial.println();
    if (EEPROM.read(i) < 0x10)
      Serial.print('0');
    Serial.print(EEPROM.read(i), HEX);
    Serial.print(' ');
  }
}

void changeSettings()
{
  fileIsLoad = false;
  if (Serial.available())
  {
    c = Serial.read();
    Serial.print(c);
    if (c == 'm')
    {
      loadFromSerial();
      fileIsLoad = true;
      cpuInit();
      return;
    }
    else if (c == 'r')
    {
      ESP.reset();
      return;
    }
    else if (c == 'd')
    {
      debug();
      Serial.print(F("kIPS"));
      Serial.println(cpuOPSD, DEC);
      return;
    }
    else if (c == 'e')
    {
      viewEEPROM();
    }
    else if (c == 'v')
    {
      Serial.println();
      Serial.println(F("input new resolution"));
      int w = 0;
      int h = 0;
      while (Serial.available() == 0)
      {
      }
      c = Serial.read();
      if (c <= 47 || c > 57)
      {
        while (Serial.available() == 0)
        {
        }
        c = Serial.read();
      }
      while (c > 47 && c <= 57)
      {
        w = w * 10 + (c - 48);
        while (Serial.available() == 0)
        {
        }
        c = Serial.read();
      }
      Serial.print(w);
      Serial.print(' ');
      while (Serial.available() == 0)
      {
      }
      c = Serial.read();
      while (c > 47 && c <= 57)
      {
        h = h * 10 + (c - 48);
        while (Serial.available() == 0)
        {
        }
        c = Serial.read();
      }
      Serial.println(h);
      setScreenResolution(w, h);
      return;
    }
  }
}

void coos_cpu(void)
{
  while (1)
  {
    COOS_DELAY(0); // 1 ms
    timeR = millis();
    cpuOPS += 1;
    cpuRun(1000);
    timeCpu += millis() - timeR;
    if (delay_rtttl <= 0)
      delay_rtttl = playRtttl();
  }
}

void coos_screen(void)
{
  while (1)
  {
    yield();
    COOS_DELAY(timeForRedraw);
    timeR = millis();
    clearSpriteScr();
    redrawSprites();
    moveSprites();
    testSpriteCollision();
    redrawParticles();
    timeSpr += millis() - timeR;
    timeR = millis();
    redrawScreen();
    setRedraw();
    timeGpu += millis() - timeR;
    cadr_count++;
    if (millis() - timeF > 1000)
    {
      timeF = millis();
      fps = cadr_count;
      cadr_count = cadr_count % 2;
    }
  }
}

void IRAM_ATTR timer_tick(void)
{
  for (int16_t i = 0; i < 8; i++)
  {
    if (timers[i] >= 1)
      timers[i]--;
  }
  delay_rtttl--;
  updateRtttl();
}

void coos_key(void)
{
  while (1)
  {
    COOS_DELAY(100); // 100 ms
    getKey();
    if (thiskey == 192) // key select + start
      pause();
    if (!serial_used)
      changeSettings();
  }
}

void coos_info(void)
{
  while (1)
  {
    COOS_DELAY(1000); // 1000 ms
#ifdef DEBUG_ON_SCREEN
    if (getDisplayXOffset() > 30)
    {
      tft.fillRect(0, 0, 30, 92, 0x0000);
      tft.setCursor(1, 0);
      tft.println("fps");
      tft.println(fps);
      tft.println("cpu");
      tft.println(timeCpu, DEC);
      tft.println("gpu");
      tft.println(timeGpu, DEC);
      tft.println("spr");
      tft.println(timeSpr, DEC);
      tft.println("kIPS");
      tft.println(cpuOPS, DEC);
    }
#endif
    timeCpu = 0;
    timeGpu = 0;
    timeSpr = 0;
    cpuOPSD = cpuOPS;
    cpuOPS = 0;
  }
}

void setup()
{
  // system_update_cpu_freq(FREQUENCY);
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  Serial.println();
  Serial.print(F("version "));
  Serial.print(F(BUILD_VERSION));
  Serial.print(F(" build "));
  Serial.print(F(__DATE__));
  randomSeed(RANDOM_REG32);
  // init keyboard
  keyboardInit();

  tft.init(); // initialize LCD
  tft.setRotation(SCREEN_ROTATION);
  tft.fillScreen(0x0000);

  // Initialize File System
  LittleFSConfig cfg;
  cfg.setAutoFormat(false);
  LittleFS.setConfig(cfg);
  tft.setTextColor(TFT_GREEN);
  if (LittleFS.begin())
  {
    Serial.println(F("LittleFS Initialize....ok"));
  }
  else
  {
    tft.setCursor(2, 0);
    tft.print(F("LittleFS init FAILED"));
    tft.setCursor(2, 10);
    tft.print(F("FORMATING..."));
    Serial.println(F("LittleFS init FAILED. Formating..."));
    if (LittleFS.format())
    {
      Serial.println(F("Formating DONE"));
      tft.setCursor(2, 18);
      tft.print(F("DONE!"));
      LittleFS.begin();
      delay(2000);
    }
    else
    {
      Serial.println(F("Formatting FAILED"));
      tft.setCursor(2, 18);
      tft.print(F("Formatting FAILED"));
      delay(2000);
    }
  }

  // turn off ESP8266 RF
  // WiFiOff();
  // delay(1);
  memoryAlloc();
  loadSplashscreen();
  cpuInit();
  Serial.print(F("FreeHeap:"));
  Serial.println(ESP.getFreeHeap());
  Serial.println(F("print \"vW H\" for change viewport, \"d name\" for delite file,"));
  Serial.println(F("\"s name\" for save file and \"m\" for load to memory"));

  setScreenResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
  clearScr(0);
  setColor(1);
  timer.attach(0.001, timer_tick);
  coos.register_task(coos_cpu);
  coos.register_task(coos_screen);
  coos.register_task(coos_key);
  coos.register_task(coos_info);
  coos.start(); // init registered tasks
}

void loop()
{
  coos.run(); // Coos scheduler
}
