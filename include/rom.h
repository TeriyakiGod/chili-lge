#ifndef ROM_HPP
#define ROM_HPP

#include <Arduino.h>
#include "settings.h"

// Declare external variables
extern char* romName;
extern const uint8_t rom[] PROGMEM;
extern const uint8_t romImage[] PROGMEM;

// Function prototypes
void loadSplashscreen();
void loadRom();
void loadRomIco();

#endif // ROM_HPP
