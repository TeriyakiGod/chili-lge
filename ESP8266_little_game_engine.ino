#include <Arduino.h>
#include <Ticker.h>
#include <SPI.h>
#include <Wire.h>
#include <FS.h>
#include <TFT_eSPI.h>
#include <EEPROM.h>
#include "acoos.h"

#include "settings.h"
#ifdef ESPBOY
  #include "ESPboyLogo.h"
  #include <Adafruit_MCP23017.h>
  #include <Adafruit_MCP4725.h>
  #include <FastLED.h>
#endif

Coos <5, 0> coos;

// Use hardware SPI
TFT_eSPI tft = TFT_eSPI();

#ifdef ESPBOY
Adafruit_MCP23017 mcp;
Adafruit_MCP4725 dac;
CRGB leds[1];
#endif

// ------------------begin ESP8266'centric----------------------------------
#include "ESP8266WiFi.h"
extern "C" {
  #include "user_interface.h"
}
// ------------------end ESP8266'centric------------------------------------
uint8_t i2c_adress;
uint8_t thiskey;
char c;
Ticker timer;
uint16_t cadr_count = 0;
uint16_t rtttl_delay = 0;
unsigned long timeF,timeR;
uint16_t timeCpu = 0,timeGpu = 0,timeSpr = 0,cpuOPS = 0,cpuOPSD = 0;
uint8_t fps, fileIsLoad;
volatile uint16_t timers[8];
uint8_t mem[RAM_SIZE] = {
  0x90,0x00,0x42,0x02,0x11,0x01,0xD4,0x21,0x01,0x01,0x3C,0x08,0x12,0x00,0x54,0x12,0x55,0x00,0xD0,0x00,
  0x11,0x01,0x01,0x02,0x5C,0x02,0xD5,0x12,0x11,0x02,0x01,0x02,0x5C,0x03,0xD5,0x12,0x11,0x03,0x01,0x02,
  0x5C,0x04,0xD5,0x12,0x11,0x04,0x01,0x02,0xFC,0x06,0xD5,0x12,0x11,0x05,0x01,0x02,0x5C,0x05,0xD5,0x12,
  0x11,0x01,0x06,0x01,0x02,0x00,0x04,0x10,0x02,0x00,0x12,0x04,0xC1,0x12,0xC2,0x12,0xB1,0x00,0x92,0x00,
  0x80,0x00,0x04,0x10,0x02,0x00,0x12,0x03,0x13,0x14,0xF1,0x23,0x04,0x10,0x02,0x00,0x12,0x04,0x13,0x10,
  0xF1,0x23,0x04,0x10,0x02,0x00,0x12,0x05,0x13,0x20,0xF1,0x23,0x04,0x10,0x02,0x00,0x07,0x21,0xA8,0x02,
  0x06,0x02,0x02,0x00,0x90,0x00,0x42,0x00,0x11,0x03,0x12,0x06,0x01,0x03,0x4A,0x01,0xF1,0x23,0x11,0x04,
  0x12,0x02,0x13,0x14,0xF1,0x23,0x11,0x04,0x12,0x04,0x13,0x14,0xF1,0x23,0x11,0x04,0x12,0x05,0x13,0x20,
  0xF1,0x23,0x11,0x05,0x12,0x03,0x13,0x14,0xF1,0x23,0x11,0x05,0x12,0x04,0x13,0x1A,0xF1,0x23,0x11,0x05,
  0x12,0x05,0x13,0x20,0xF1,0x23,0x11,0x01,0x12,0x14,0x01,0x03,0xE0,0xFF,0xE1,0x23,0x11,0x02,0x12,0x36,
  0x01,0x03,0xE0,0xFF,0xE1,0x23,0x11,0x05,0x12,0x54,0x01,0x03,0xE0,0xFF,0xE1,0x23,0x11,0x01,0x12,0x01,
  0xDC,0x12,0x12,0x40,0xC1,0x12,0xC2,0x12,0xB1,0x00,0x92,0x00,0xEE,0x00,0x90,0x00,0xD8,0x00,0x11,0x01,
  0x06,0x01,0x02,0x00,0x04,0x10,0x02,0x00,0x12,0x04,0xC1,0x12,0xC2,0x12,0xB1,0x00,0x92,0x00,0x20,0x01,
  0x04,0x10,0x02,0x00,0x12,0x03,0x01,0x03,0xF6,0xFF,0xF1,0x23,0x04,0x10,0x02,0x00,0x07,0x21,0xA8,0x02,
  0x06,0x02,0x02,0x00,0x90,0x00,0xF4,0x00,0x11,0x03,0x12,0x5A,0x13,0x01,0x14,0x01,0xDC,0x34,0xE1,0x23,
  0x11,0x05,0x12,0x07,0x13,0x00,0xF1,0x23,0x11,0x03,0x12,0x06,0x01,0x03,0x50,0x01,0xF1,0x23,0x99,0x00,
  0x52,0x02,0x99,0x00,0x52,0x02,0x11,0x03,0x12,0x06,0x01,0x03,0x52,0x01,0xF1,0x23,0x99,0x00,0x52,0x02,
  0x99,0x00,0x52,0x02,0x11,0x03,0x12,0x06,0x01,0x03,0x56,0x01,0xF1,0x23,0x99,0x00,0x52,0x02,0x99,0x00,
  0x52,0x02,0x11,0x03,0x12,0x06,0x01,0x03,0x5E,0x01,0xF1,0x23,0x99,0x00,0x52,0x02,0x99,0x00,0x52,0x02,
  0x11,0x03,0x12,0x06,0x13,0x00,0xF1,0x23,0x99,0x00,0x52,0x02,0x11,0x01,0x12,0x01,0xDC,0x12,0x12,0x30,
  0xC1,0x12,0xC2,0x13,0xB1,0x00,0x92,0x00,0x9E,0x01,0x90,0x00,0x88,0x01,0x11,0x01,0x06,0x01,0x02,0x00,
  0x04,0x10,0x02,0x00,0x12,0x04,0xC1,0x12,0xC2,0x12,0xB1,0x00,0x92,0x00,0xCE,0x01,0x04,0x10,0x02,0x00,
  0x12,0x03,0x13,0x00,0xF1,0x23,0x04,0x10,0x02,0x00,0x07,0x21,0xA8,0x02,0x06,0x02,0x02,0x00,0x90,0x00,
  0xA4,0x01,0x11,0x04,0x12,0x00,0x13,0x01,0x14,0x01,0xDC,0x34,0xE1,0x23,0x11,0x04,0x12,0x00,0xDC,0x12,
  0x12,0x80,0xC1,0x12,0xC2,0x12,0xB1,0x00,0x92,0x00,0xF0,0x01,0x90,0x00,0xDA,0x01,0x11,0x01,0x01,0x02,
  0xE8,0x03,0x51,0x12,0x11,0x01,0x52,0x01,0xB1,0x00,0x92,0x00,0x06,0x02,0x90,0x00,0xF8,0x01,0x11,0x01,
  0x06,0x01,0x02,0x00,0x04,0x10,0x02,0x00,0x12,0x05,0xC1,0x12,0xC2,0x12,0xB1,0x00,0x92,0x00,0x36,0x02,
  0x04,0x10,0x02,0x00,0x12,0x07,0x13,0x00,0xF1,0x23,0x04,0x10,0x02,0x00,0x07,0x21,0xA8,0x02,0x06,0x02,
  0x02,0x00,0x90,0x00,0x0C,0x02,0xD0,0x00,0x99,0x00,0x52,0x02,0x99,0x00,0x52,0x02,0x9A,0x00,0x01,0x0F,
  0x00,0x00,0x06,0xF0,0x1D,0x09,0xA9,0x20,0x99,0x00,0x04,0x00,0x50,0x00,0xC2,0x16,0xB1,0x00,0x92,0x00,
  0x52,0x02,0x9A,0x00,0x04,0x44,0x40,0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x24,0x00,0x00,0x00,0x00,0x00,
  0x42,0x22,0x44,0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x24,0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x44,0x00,
  0x00,0x00,0x00,0x00,0x42,0x22,0x24,0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x24,0x00,0x00,0x00,0x00,0x00,
  0x42,0x22,0x44,0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x24,0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x44,0x00,
  0x00,0x00,0x00,0x00,0x42,0x22,0x24,0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x24,0x00,0x00,0x00,0x00,0x00,
  0x42,0x22,0x44,0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x24,0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x44,0x00,
  0x00,0x00,0x00,0x00,0x42,0x22,0x24,0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x24,0x00,0x00,0x00,0x00,0x00,
  0x42,0x22,0x44,0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x24,0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x44,0x00,
  0x00,0x00,0x00,0x00,0x42,0x22,0x24,0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x24,0x00,0x00,0x00,0x00,0x00,
  0x42,0x22,0x44,0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x24,0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x44,0x00,
  0x00,0x00,0x00,0x00,0x42,0x22,0x24,0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x22,0x44,0x44,0x44,0x44,0x40,
  0x42,0x22,0x22,0x22,0x22,0x22,0x24,0x24,0x42,0x22,0x22,0x22,0x22,0x22,0x22,0x44,0x42,0x22,0x22,0x22,
  0x22,0x22,0x24,0x24,0x04,0x22,0x22,0x22,0x22,0x22,0x22,0x44,0x00,0x44,0x44,0x44,0x44,0x44,0x44,0x40,
  0x06,0x66,0x66,0x66,0x66,0x66,0x66,0x60,0x63,0x33,0x33,0x33,0x33,0x33,0x33,0x36,0x63,0x33,0x33,0x33,
  0x33,0x33,0x33,0x66,0x63,0x33,0x33,0x33,0x33,0x33,0x33,0x36,0x63,0x33,0x33,0x33,0x33,0x33,0x33,0x36,
  0x63,0x33,0x36,0x66,0x66,0x63,0x33,0x36,0x63,0x33,0x36,0x00,0x00,0x63,0x33,0x36,0x63,0x33,0x66,0x00,
  0x00,0x63,0x33,0x36,0x63,0x33,0x36,0x00,0x00,0x06,0x66,0x60,0x63,0x33,0x66,0x00,0x00,0x00,0x00,0x00,
  0x63,0x33,0x36,0x00,0x00,0x00,0x00,0x00,0x63,0x33,0x36,0x00,0x00,0x00,0x00,0x00,0x63,0x33,0x66,0x00,
  0x00,0x00,0x00,0x00,0x63,0x33,0x36,0x00,0x00,0x00,0x00,0x00,0x63,0x33,0x66,0x00,0x00,0x00,0x00,0x00,
  0x63,0x33,0x36,0x00,0x00,0x00,0x00,0x00,0x63,0x33,0x36,0x00,0x00,0x00,0x00,0x00,0x63,0x33,0x66,0x00,
  0x00,0x00,0x00,0x00,0x63,0x33,0x36,0x00,0x66,0x66,0x66,0x60,0x63,0x33,0x66,0x06,0x33,0x33,0x33,0x36,
  0x63,0x33,0x36,0x06,0x33,0x33,0x33,0x66,0x63,0x33,0x36,0x06,0x33,0x33,0x33,0x36,0x63,0x33,0x66,0x06,
  0x33,0x33,0x33,0x36,0x63,0x33,0x36,0x00,0x66,0x66,0x33,0x66,0x63,0x33,0x66,0x00,0x00,0x06,0x33,0x36,
  0x63,0x33,0x36,0x00,0x00,0x06,0x33,0x66,0x63,0x33,0x33,0x66,0x66,0x66,0x33,0x36,0x63,0x33,0x33,0x33,
  0x33,0x33,0x33,0x36,0x63,0x33,0x33,0x33,0x33,0x33,0x33,0x66,0x63,0x33,0x33,0x33,0x33,0x33,0x33,0x36,
  0x63,0x33,0x33,0x33,0x33,0x33,0x33,0x66,0x06,0x66,0x66,0x66,0x66,0x66,0x66,0x60,0x09,0x99,0x99,0x99,
  0x99,0x99,0x99,0x90,0x9D,0xDD,0xDD,0xDD,0xDD,0xDD,0xDD,0xD9,0x9D,0xDD,0xDD,0xDD,0xDD,0xDD,0xDD,0x99,
  0x9D,0xDD,0xDD,0xDD,0xDD,0xDD,0xDD,0xD9,0x9D,0xDD,0xDD,0xDD,0xDD,0xDD,0xDD,0x99,0x9D,0xDD,0xD9,0x99,
  0x99,0x99,0x99,0x90,0x9D,0xDD,0xD9,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0x99,0x00,0x00,0x00,0x00,0x00,
  0x9D,0xDD,0xD9,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0x99,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0xD9,0x00,
  0x00,0x00,0x00,0x00,0x9D,0xDD,0xD9,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0x99,0x99,0x99,0x90,0x00,0x00,
  0x9D,0xDD,0xDD,0xDD,0xDD,0xD9,0x00,0x00,0x9D,0xDD,0xDD,0xDD,0xDD,0x99,0x00,0x00,0x9D,0xDD,0xDD,0xDD,
  0xDD,0xD9,0x00,0x00,0x9D,0xDD,0xDD,0xDD,0xDD,0x99,0x00,0x00,0x9D,0xDD,0x99,0x99,0x99,0x90,0x00,0x00,
  0x9D,0xDD,0xD9,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0x99,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0xD9,0x00,
  0x00,0x00,0x00,0x00,0x9D,0xDD,0xD9,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0x99,0x00,0x00,0x00,0x00,0x00,
  0x9D,0xDD,0xD9,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0x99,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0xD9,0x00,
  0x00,0x00,0x00,0x00,0x9D,0xDD,0xDD,0x99,0x99,0x99,0x99,0x90,0x9D,0xDD,0xDD,0xDD,0xDD,0xDD,0xDD,0xD9,
  0x9D,0xDD,0xDD,0xDD,0xDD,0xDD,0xDD,0x99,0x9D,0xDD,0xDD,0xDD,0xDD,0xDD,0xDD,0xD9,0x9D,0xDD,0xDD,0xDD,
  0xDD,0xDD,0xDD,0x99,0x09,0x99,0x99,0x99,0x99,0x99,0x99,0x90,0x00,0x00,0x00,0x00,0x00,0x09,0x90,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x9D,0x99,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x09,0x9D,0xDD,0xD9,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x9D,0xDD,0xDD,0x9D,0x90,0x00,
  0x00,0x00,0x00,0x00,0x00,0x09,0x9D,0xDD,0xDD,0xDD,0xDD,0x90,0x00,0x00,0x00,0x00,0x00,0x09,0x9D,0xDD,
  0xDD,0xDD,0xDD,0x99,0x00,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0xDD,0xDD,0xDD,0x99,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x9D,0xDD,0xDD,0xDD,0x99,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0xDD,0xDD,0xD9,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0xDD,0xDD,0x9D,0x90,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x9D,0xDD,0xDD,0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0xD9,0xD9,
  0x00,0x00,0x99,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0xDD,0xDD,0xD9,0x00,0x99,0xD9,0x90,0x00,0x00,0x00,
  0x00,0x00,0x09,0xDD,0xDD,0x9D,0x99,0xDD,0xDD,0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0xDD,0xDD,
  0xDD,0xD9,0xD9,0x00,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0xDD,0xDD,0xDD,0xDD,0xD9,0x00,0x00,0x00,0x00,
  0x00,0x00,0x09,0xDD,0xDD,0xDD,0xDD,0xD9,0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0xDD,0xDD,0xDD,0xD9,
  0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0xDD,0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x9D,0xDD,0xDD,0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0xDD,0xD9,0xD9,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0xDD,0xDD,0xD9,0x00,0x00,0x00,0x09,0x90,0x00,0x00,0x00,
  0x00,0x00,0x9D,0xDD,0x9D,0x90,0x00,0x09,0x9D,0x99,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0xDD,0x90,0x09,
  0xDD,0xDD,0xD9,0x00,0x00,0x00,0x00,0x00,0x09,0xDD,0xD9,0xD9,0x9D,0xDD,0xDD,0x9D,0x90,0x00,0x00,0x00,
  0x00,0x09,0xDD,0xDD,0xDD,0xDD,0xDD,0xDD,0xDD,0x90,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0xDD,0xDD,0xDD,
  0xDD,0x99,0x00,0x00,0x00,0x00,0x00,0x00,0x9D,0xDD,0xDD,0xDD,0xDD,0xD9,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x09,0xDD,0xDD,0xDD,0x99,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0xDD,0xDD,0x99,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x9D,0x99,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x11,0x11,0x11,0x00,0x00,
  0x00,0x00,0x00,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x10,0x00,0x00,
  0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x10,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x10,0x00,0x00,
  0x00,0x00,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,
  0x00,0x00,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x10,0x00,0x00,0x00,
  0x00,0x01,0x11,0x11,0x11,0x11,0x10,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x10,0x00,0x00,0x00,
  0x00,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,
  0x00,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x10,0x00,0x00,0x00,0x00,
  0x01,0x11,0x11,0x11,0x11,0x10,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x10,0x00,0x00,0x00,0x00,
  0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,
  0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x10,0x00,0x00,0x00,0x00,0x01,
  0x11,0x11,0x11,0x11,0x10,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x10,0x00,0x00,0x00,0x00,0x11,
  0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x11,
  0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x10,0x00,0x00,0x00,0x00,0x01,0x11,
  0x11,0x11,0x11,0x10,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x10,0x00,0x00,0x00,0x00,0x11,0x11,
  0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x11,0x11,
  0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x73,0x3A,0x64,0x3D,0x34,0x2C,0x6F,0x3D,0x37,0x2C,0x62,0x3D,
  0x39,0x30,0x30,0x3A,0x64,0x23,0x2C,0x66,0x23,0x2C,0x65,0x2C,0x34,0x65,0x34,0x2C,0x65,0x2C,0x67,0x2C,
  0x66,0x2C,0x34,0x63,0x34,0x2C,0x66,0x2C,0x67,0x23,0x2C,0x66,0x23,0x2C,0x34,0x65,0x34,0x2C,0x66,0x23,
  0x2C,0x61,0x2C,0x67,0x2C,0x34,0x63,0x34,0x2C,0x67,0x2C,0x61,0x23,0x2C,0x67,0x23,0x2C,0x34,0x65,0x34,
  0x2C,0x67,0x23,0x2C,0x62,0x2C,0x61,0x2C,0x34,0x63,0x34,0x2C,0x67,0x23,0x2C,0x67,0x2C,0x66,0x23,0x2C,
  0x34,0x65,0x34,0x2C,0x66,0x2C,0x65,0x2C,0x64,0x23,0x2C,0x34,0x63,0x34,0x2C,0x64,0x2C,0x63,0x23,0x2C,
  0x63,0x2C,0x34,0x65,0x34,0x2C,0x64,0x23,0x2C,0x66,0x2C,0x64,0x23,0x2C,0x34,0x63,0x34,0x2C,0x64,0x23,
  0x2C,0x66,0x2C,0x64,0x23,0x2C,0x34,0x63,0x34,0x2C,0x64,0x23,0x2C,0x66,0x2C,0x64,0x23,0x2C,0x34,0x63,
  0x34,0x2C,0x64,0x23,0x2C,0x66,0x2C,0x64,0x23,0x2C,0x70,0x2C,0x70,0x2C,0x33,0x32,0x66,0x23,0x35,0x2C,
  0x33,0x32,0x65,0x36,0x2C,0x33,0x32,0x63,0x23,0x35,0x2C,0x33,0x32,0x66,0x23,0x34,0x2C,0x33,0x32,0x63,
  0x34,0x2C,0x33,0x32,0x67,0x34,0x2C,0x33,0x32,0x66,0x34,0x2C,0x33,0x32,0x64,0x34,0x2C,0x33,0x32,0x65,
  0x34,0x2C,0x33,0x32,0x63,0x23,0x34,0x2C,0x33,0x32,0x65,0x34,0x00
};

static const uint16_t bpalette[] = {
    0x0020, 0xE718, 0xB9A8, 0x7DB6, 0x61EB, 0x6D2D, 0x21EC, 0xD5CA,
    0xAC4D, 0x42CB, 0xBB09, 0x3186, 0x73AE, 0x8D4B, 0x3DF9, 0xBDD7
};
uint16_t palette[16] __attribute__ ((aligned));
uint16_t sprtpalette[16] __attribute__ ((aligned));

uint16_t bgr_to_rgb(uint16_t c){
  return ((c & 0x001f) << 11) + ((c & 0xf800) >> 11) + (c & 0x07e0);
}

unsigned char hexToByte(char h){
  if(h < 48)
    return 48;
  if (h >= 48 && h <= 57) 
    h = map(h, 48, 57, 0, 9);
  else if (h >= 65 && h <= 70) 
    h = map(h, 65, 70, 10, 15);
  else if (h >= 97 && h <= 102) 
    h = map(h, 97, 102, 10, 15);
  return h;
}

void loadFromSerial(){
  char c;
  unsigned char n;
  int16_t j = 0;
  for(int16_t i = 0; i < RAM_SIZE; i++)
    mem[i] = 0;
  while(c != '.'){
    if(Serial.available()){
      c = Serial.read();
      Serial.print(c);
      if(c == '$'){
        n = 48;
        while(n > 15){
          c = Serial.read();
          n = hexToByte(c);
        }
        Serial.print(c);
        mem[j] = n << 4;
        n = 48;
        while(n > 15){
          c = Serial.read();
          n = hexToByte(c);
        }
        Serial.print(c);
        mem[j] += n;
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

void viewEEPROM(){
  for(int16_t i = 0; i < EEPROM_SIZE; i++){
    if(i % 32 == 0)
      Serial.println();
    if(EEPROM.read(i) < 0x10)
      Serial.print('0');
    Serial.print(EEPROM.read(i), HEX);
    Serial.print(' ');
  }
}

void changeSettings(){
  fileIsLoad = false;
  if(Serial.available()){
    c = Serial.read();
    Serial.print(c);
    if(c == 'm'){
      loadFromSerial();
      fileIsLoad = true;
      cpuInit();
      return;
    }
    else if(c == 'r'){
      ESP.reset();
      return;
    }
    else if(c == 'd'){
      debug();
      Serial.print(F("kIPS"));
      Serial.println(cpuOPSD, DEC);
      return;
    }
    else if(c == 'e'){
      viewEEPROM();
    }
    else if(c == 'v'){
      Serial.println();
      Serial.println(F("input new resolution"));
      int w = 0;
      int h = 0;
      while(Serial.available() == 0){}
      c = Serial.read();
      if(c <= 47 || c > 57){
        while(Serial.available() == 0){}
        c = Serial.read();
      }
      while(c > 47 && c <= 57){
        w = w * 10 + (c - 48);
        while(Serial.available() == 0){}
        c = Serial.read();
      }
      Serial.print(w);
      Serial.print(' ');
      while(Serial.available() == 0){}
      c = Serial.read();
      while(c > 47 && c <= 57){
        h = h * 10 + (c - 48);
        while(Serial.available() == 0){}
        c = Serial.read();
      }
      Serial.println(h);
      setScreenResolution(w, h);
      return;
    }
  }
}

void coos_cpu(void){   
  while(1){
    COOS_DELAY(0);        // 1 ms
    timeR = millis();
    cpuOPS += 1;
    cpuRun(1000);
    timeCpu += millis() - timeR;
  }
}

void coos_screen(void){
   while(1){
    yield();
    COOS_DELAY(50);        // 50 ms
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
    if(millis() - timeF > 1000){
      timeF = millis();
      fps = cadr_count;
      cadr_count = cadr_count % 2;
    }  
  } 
}

void timer_tick(void){
  for(int8_t i = 0; i < 8; i++){
    if(timers[i] >= 1)
      timers[i] --;
  }
}

void coos_key(void){   
  while(1){
    COOS_DELAY(100);        // 100 ms
    getKey();
    if(thiskey & 128)
      pause();
    changeSettings();
  }
}

void coos_rtttl(void){
  while(1){
    rtttl_delay = playRtttl();
    if(rtttl_delay){
      if(rtttl_delay > 10)
        rtttl_delay -= 10;
      COOS_DELAY(rtttl_delay);
    }
    else
      COOS_DELAY(100);
  }
}

void coos_info(void){   
  while(1){
    COOS_DELAY(1000);        // 1000 ms
   #ifdef DEBUG_ON_SCREEN
    if(getDisplayXOffset() > 30){
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

void setup() {
  // ------------------begin ESP8266'centric----------------------------------
  delay(1);                                // give RF section time to shutdown
  system_update_cpu_freq(FREQUENCY);
  // ------------------end ESP8266'centric------------------------------------
  Serial.begin (115200);
  EEPROM.begin(EEPROM_SIZE);
 #ifdef ESPBOY
  Wire.begin();
  Serial.println();
  Serial.println(F("ESPboy"));
  scani2c();
  //DAC init
  dac.begin(MCP4725address);
  delay(100);
  dac.setVoltage(0, true);
  //buttons on mcp23017 init
  mcp.begin(MCP23017address);
  delay (100);
  for(int i = 0; i < 8; i++){
     mcp.pinMode(i, INPUT);
     mcp.pullUp(i, HIGH);
  }
  FastLED.addLeds<WS2812B, LEDPIN, RGB>(leds, 1);
  leds[0] = CRGB::Black;
  FastLED.show();
  FastLED.show();
  delay(50);
  //initialize LCD
  mcp.pinMode(csTFTMCP23017pin, OUTPUT);
  mcp.digitalWrite(csTFTMCP23017pin, LOW);
  tft.init();            
  tft.setRotation(0);
  tft.fillScreen(0x0000);
  tft.setTextSize(1);
  tft.drawXBitmap(30, 24, ESPboyLogo, 68, 64, 0xFFE0);
  tft.setTextColor(0xFFE0);
  tft.setCursor(10,102);
  tft.print(F("Little game engine"));
  //sound init and test
  pinMode(SOUNDPIN, OUTPUT);
  tone(SOUNDPIN, 200, 100);
  delay(100);
  tone(SOUNDPIN, 100, 100);
  delay(100);
  noTone(SOUNDPIN);
  //LCD backlit on
  for (int count = 0; count < 1000; count += 50){
    dac.setVoltage(count, false);
    delay(50);
  }
  dac.setVoltage(4095, true);
  delay(1000);
 #else
  Wire.begin(D2, D1);
  geti2cAdress();
  tft.init();            // initialize LCD
  tft.setRotation(1);
 #endif
  tft.fillScreen(0x0000);
  tft.setTextSize(1);
  tft.setTextColor(0xffff);
  //Initialize File System
  if(SPIFFS.begin()){
    Serial.println(F("SPIFFS Initialize....ok"));
  }
  else{
    Serial.println(F("SPIFFS Initialization...failed"));
  }
  randomSeed(ESP.getVcc());
  getKey();
  //go to web file manager
  if(thiskey & 32){//key B
    serverSetup();
    tft.setCursor(0,10);
    tft.print(F("SSID "));
    tft.print(F(APSSID));
    tft.print(F("\nPassword "));
    tft.print(F(APPSK));
    tft.print(F("\nGo to \nhttp://192.168.4.1"));
    tft.print(F("\nin a web browser"));
    tft.print(F("\nPress button A to\nreboot"));
    while(1){
      serverLoop();
      getKey();
      if(Serial.read() == 'r' || thiskey & 16)
        ESP.reset();
      delay(100);
    }
  }
  else{
    // turn off ESP8266 RF
    WiFi.forceSleepBegin();
    delay(1);
  }
  memoryAlloc();
  cpuInit();
  Serial.print(F("FreeHeap:"));
  Serial.println(ESP.getFreeHeap());
  Serial.println(F("print \"vW H\" for change viewport, \"d name\" for delite file,"));
  Serial.println(F("\"s name\" for save file and \"m\" for load to memory"));
 #ifdef ESPBOY
  setScreenResolution(128, 128);
 #else
  setScreenResolution(239, 239);
 #endif
  clearScr(0);
  setColor(1);
  randomSeed(analogRead(0));
  timer.attach(0.001, timer_tick);
  coos.register_task(coos_cpu); 
  coos.register_task(coos_screen);   
  coos.register_task(coos_key); 
  coos.register_task(coos_rtttl);
  coos.register_task(coos_info);
  coos.start();                     // init registered tasks
}

void loop() {
  coos.run();  // Coos scheduler
}
