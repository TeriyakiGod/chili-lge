#ifndef ESP_LGE_HPP
#define ESP_LGE_HPP

#include <Arduino.h>
#include <Ticker.h>
#include "settings.h"
#include "acoos.h"
#include <TFT_eSPI.h>

extern TFT_eSPI tft;
extern Coos<4, 0> coos;

extern uint8_t i2c_adress;
extern uint8_t serial_used;
extern char c;
extern Ticker timer;
extern int delay_rtttl;
extern uint16_t cadr_count;
extern unsigned long timeF, timeR;
extern uint16_t timeCpu, timeGpu, timeSpr, cpuOPS, cpuOPSD;
extern uint8_t fps, fileIsLoad;
extern uint8_t timeForRedraw;
extern uint8_t fixed_res_bit;
extern volatile uint16_t timers[8];

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
