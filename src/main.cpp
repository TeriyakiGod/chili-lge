#include <LittleFS.h>
#include <EEPROM.h>
#include <lge_memory.h>
#include <sound.h>
#include <coos.h>
#include <display.h>
#include <input.h>
#include <rom.h>
#include <cpu.h>

void setup() {
    Serial.begin(MONITOR_SPEED);
    EEPROM.begin(EEPROM_SIZE);
    initializeDisplay();
    if (!LittleFS.begin()) {
      LittleFS.format();
    }
    memoryAlloc();
    loadSplashscreen();
    cpuInit();
    keyboardInit();

    setScreenResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
    clearScr(0);
    setColor(1);

    initCoos();
}

void loop()
{
  coosScheduler();
}
