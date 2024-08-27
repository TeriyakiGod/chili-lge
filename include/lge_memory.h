#ifndef LGE_MEMORY_HPP
#define LGE_MEMORY_HPP

#include <Arduino.h>
#include "settings.h"

extern uint8_t *lge_mem __attribute__ ((aligned));

void memoryAlloc();
void memoryFree();

inline void writeMem(uint16_t adr, int16_t n)
{
    if (adr < RAM_SIZE)
        lge_mem[adr] = n;
}

inline uint8_t readMem(uint16_t adr)
{
    return (adr < RAM_SIZE) ? lge_mem[adr] : 0;
}

inline void writeInt(uint16_t adr, int16_t n)
{
    if (adr < RAM_SIZE - 1)
    {
        int8_t *nPtr = reinterpret_cast<int8_t *>(&n);
        lge_mem[adr++] = *nPtr;
        nPtr++;
        lge_mem[adr] = *nPtr;
    }
}

inline int16_t readInt(uint16_t adr)
{
    int16_t n;
    if (adr < RAM_SIZE - 1)
    {
        int8_t *nPtr = reinterpret_cast<int8_t *>(&n);
        *nPtr = lge_mem[adr++];
        nPtr++;
        *nPtr = lge_mem[adr];
        return n;
    }
    return 0;
}

#endif // LGE_MEMORY_HPP