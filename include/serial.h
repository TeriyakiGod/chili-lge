#ifndef IO_HPP
#define IO_HPP

#include <Arduino.h> 

extern uint8_t serial_used;

int16_t serialBegin();
int16_t serialAvailable();
int16_t serialRead();
int16_t serialWrite(int16_t n);

void keyboardInit();
void getKey();

#endif // IO_HPP
