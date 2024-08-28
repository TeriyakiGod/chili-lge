#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>

// 8 bits: UP DOWN LEFT RIGHT A SELECT B START
extern uint8_t thiskey;

void keyboardInit();
void getKey();

#endif // INPUT_H