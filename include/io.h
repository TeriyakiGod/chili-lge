#ifndef IO_HPP
#define IO_HPP

#include <Arduino.h>  // For Arduino functions and types
#include "settings.h"

// Serial communication functions
int16_t serialBegin();
int16_t serialAvailable();
int16_t serialRead();
int16_t serialWrite(int16_t n);

// Function to initialize keyboard pins
void keyboardInit();

// Function to read key states
void getKey();

#endif // IO_HPP
