#ifndef COOS_H
#define COOS_H

#include <Arduino.h>
#include <acoos.h>
#include <Ticker.h>

extern Ticker timer;
extern volatile uint16_t timers[8];

void initCoos();
void coosScheduler();

#endif // COOS_H