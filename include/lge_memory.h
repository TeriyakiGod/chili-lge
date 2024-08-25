#ifndef LGE_MEMORY_HPP
#define LGE_MEMORY_HPP

#include <Arduino.h>
#include "settings.h"

// Declare the external memory pointer
extern uint8_t *lge_mem;

// Function prototypes
void memoryAlloc();
void memoryFree();
void writeMem(uint16_t adr, int16_t n);
uint8_t readMem(uint16_t adr);
void writeInt(uint16_t adr, int16_t n);
int16_t readInt(uint16_t adr);

#endif // LGE_MEMORY_HPP