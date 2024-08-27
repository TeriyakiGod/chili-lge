#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>

extern uint8_t thiskey;

void keyboardInit();
void getKey();

#endif // INPUT_H