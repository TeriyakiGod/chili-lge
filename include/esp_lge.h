#ifndef ESP_LGE_HPP
#define ESP_LGE_HPP

#include <Arduino.h>
#include <Ticker.h>
#include "settings.h"
#include "acoos.h"
#include <TFT_eSPI.h>

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

// Function prototypes
uint16_t bgr_to_rgb(uint16_t c);
unsigned char hexToByte(char h);
void loadFromSerial();
void viewEEPROM();
void changeSettings();
void coos_cpu(void);
void coos_screen(void);
void IRAM_ATTR timer_tick(void);
void coos_key(void);
void coos_info(void);
void setup();
void loop();

#endif // ESP_LGE_HPP
