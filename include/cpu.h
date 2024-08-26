#ifndef CPU_EMULATOR_HPP
#define CPU_EMULATOR_HPP

#include <EEPROM.h>
#include <Arduino.h>
#include "settings.h"

#define FIFO_MAX_SIZE 32

extern int16_t reg[16] __attribute__ ((aligned));
extern int16_t shadow_reg[16] __attribute__ ((aligned));
extern uint16_t pc;
extern uint16_t interrupt;
extern uint16_t dataName;
extern uint32_t accum, saccum;
extern uint8_t carry;
extern uint8_t zero;
extern uint8_t negative;
extern uint8_t redraw;
extern int8_t color;
extern int8_t bgcolor;
extern int8_t keyPosition;
extern char s_buffer[7];
extern String loadedFileName;
extern char strBuf[16];
extern uint8_t strBufLength;
extern uint8_t strBufPosition;

// FIFO Structure
struct Fifo_t {
    uint16_t el[FIFO_MAX_SIZE];
    uint8_t position_read;
    uint8_t position_write;
    uint8_t size;
};

// FIFO Instances
extern struct Fifo_t interruptFifo;

// Function Declarations
void fifoClear();
void pushInFifo(int16_t n);
uint16_t popOutFifo();

void setinterrupt(uint16_t adr, int16_t param);
void setLoadedFileName(String s);

void cpuInit();
void debug();
int16_t isqrt(int16_t n);
int16_t distancepp(int16_t x1, int16_t y1, int16_t x2, int16_t y2);

boolean testDataName(uint16_t pos);
uint16_t findData();
uint16_t findEndData();
uint16_t saveData(uint16_t arrayAddress, uint16_t count);
uint16_t loadData(uint16_t arrayAddress);

int16_t fixed_sin(int x);

void copyMem(uint16_t to_adr, uint16_t from_adr, uint16_t num_bytes);
void unpackingRLE(uint16_t to_adr, uint16_t a, uint16_t num_bytes);
void unpackingLZ(uint16_t to_adr, uint16_t a, uint16_t num_bytes);

void cpuRun(uint16_t n);

inline int16_t fixed_cos(int16_t g)
{
  return fixed_sin(g + 90);
}

inline void setDataName(uint16_t address)
{
  dataName = address;
}

inline void setRedraw()
{
  redraw = 1;
}

inline void setFlags(int32_t n)
{
  carry = (n > 0xffff) ? 1 : 0;
  negative = n >> 31;
  zero = (n == 0);
}

inline int16_t flagsTouint8_t()
{
  return (carry & 0x1) + ((zero & 0x1) << 1) + ((negative & 0x1) << 2);
}

inline void uint8_tToFlags(int16_t b)
{
  carry = b & 0x1;
  zero = (b & 0x2) >> 1;
  negative = (b & 0x4) >> 2;
}

#endif // CPU_EMULATOR_HPP
