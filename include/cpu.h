#ifndef CPU_EMULATOR_HPP
#define CPU_EMULATOR_HPP

#include <EEPROM.h>
#include <Arduino.h>
#include "settings.h"

#define FIFO_MAX_SIZE 32

// Global Variables
extern int16_t reg[16];
extern int16_t shadow_reg[16];
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
extern Fifo_t interruptFifo;

// Function Declarations
void fifoClear();
void pushInFifo(int16_t n);
uint16_t popOutFifo();

inline int16_t flagsTouint8_t();
inline void uint8_tToFlags(int16_t b);

void setinterrupt(uint16_t adr, int16_t param);
void setLoadedFileName(String s);

void cpuInit();
void debug();
inline void setRedraw();
inline void setFlags();
int16_t isqrt(int16_t n);
int16_t distancepp(int16_t x1, int16_t y1, int16_t x2, int16_t y2);

inline void setDataName();
boolean testDataName(uint16_t pos);
uint16_t findData();
uint16_t findEndData();
uint16_t saveData(uint16_t arrayAddress, uint16_t count);
uint16_t loadData(uint16_t arrayAddress);

int16_t fixed_sin(int x);
inline int16_t fixed_cos(int16_t g);

void copyMem(uint16_t to_adr, uint16_t from_adr, uint16_t num_bytes);
void unpackingRLE(uint16_t to_adr, uint16_t a, uint16_t num_bytes);
void unpackingLZ(uint16_t to_adr, uint16_t a, uint16_t num_bytes);

void cpuRun(uint16_t n);

#endif // CPU_EMULATOR_HPP
