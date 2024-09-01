#include <coos.h>
#include <cpu.h>
#include <display.h>
#include <sound.h>

Coos<4, 0> coos;
int delay_rtttl = 50;
uint16_t cadr_count = 0;
unsigned long timeF, timeR;
uint16_t timeCpu = 0, timeGpu = 0, timeSpr = 0, cpuOPS = 0, cpuOPSD = 0;
uint8_t fps;
Ticker timer;
volatile uint16_t timers[8];

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

void coos_key(void)
{
    while (1)
    {
        COOS_DELAY(100); // 100 ms
        getKey();
        if (thiskey == 192) // key select + start
            pause();
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

void initCoos() {
    timer.attach(0.001, timer_tick);
    coos.register_task(coos_cpu);
    coos.register_task(coos_screen);
    coos.register_task(coos_key);
    coos.register_task(coos_info);
    coos.start();
}

void coosScheduler() {
    coos.run();
}