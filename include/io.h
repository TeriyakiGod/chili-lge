#ifndef IO_HPP
#define IO_HPP

#include <Arduino.h>  // For Arduino functions and types
#include "settings.h"

// IO functions for Arduino

// Serial communication functions
int16_t serialBegin();
int16_t serialAvailable();
int16_t serialRead();
int16_t serialWrite(int16_t n);

// Pin definitions for NODEMCU v3
// #define PIN_D0 16  // Commented out pin, you can uncomment if needed
#define PIN_D1 5
#define PIN_D2 4
#define PIN_D3 0

// Button codes
#define BTN_UP 1
#define BTN_DOWN 2
#define BTN_LEFT 4
#define BTN_RIGHT 8
#define BTN_SELECT 16
#define BTN_A 32
#define BTN_B 64
#define BTN_START 128

// Function to initialize keyboard pins
void keyboardInit();

// Function to read key states
void getKey();

#endif // IO_HPP
