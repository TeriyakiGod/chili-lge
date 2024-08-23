#include "games/romFlatRace.h"

const uint8_t saveIco[] PROGMEM = {
  0x66, 0x66, 0x66, 0x66, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf6, 0x00, 0x00, 0x00, 0x00,
  0x66, 0x66, 0x66, 0x66, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x38, 0x88, 0x88, 0x88, 0xff, 0xf6, 0x60, 0x00, 0x00, 0x00,
  0x66, 0x66, 0x66, 0x66, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xcc, 0xcc, 0xcc, 0xff, 0xf6, 0x66, 0x60, 0x00, 0x00,
  0x66, 0x66, 0x66, 0x66, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xcc, 0xcc, 0xcc, 0xff, 0xf6, 0x66, 0x66, 0x00, 0x00,
  0x66, 0x66, 0x66, 0x66, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xcc, 0xcc, 0xcc, 0xff, 0xf6, 0x66, 0x66, 0x66, 0x00,
  0x66, 0x66, 0x66, 0x66, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xcc, 0xcc, 0xcc, 0xff, 0xf6, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xcc, 0xcc, 0xcc, 0xff, 0xf6, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xcc, 0xcc, 0xcc, 0xff, 0xf6, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc, 0xcc, 0xcc, 0xcc, 0xff, 0xf6, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf6, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x6f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x66, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x61, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x66, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x16, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x16, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x11, 0x11, 0x1d, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcd, 0x11, 0x11, 0x16, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x16, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x16, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x16, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x11, 0x11, 0x18, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xc8, 0x11, 0x11, 0x16, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x16, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x16, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x16, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x11, 0x11, 0x1c, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x11, 0x11, 0x16, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x16, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x16, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x16, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x16, 0x66, 0x66, 0x66, 0x60,
  0x66, 0x66, 0x66, 0x66, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x16, 0x66, 0x66, 0x66, 0x60,
  0x04, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0b, 0x00, 0x0b, 0x00, 0xb0, 0xb0, 0x0b, 0x00, 0x00, 0xb0, 0xb0, 0xb0, 0x0b, 0x00, 0xb0, 0xb0, 0x0b, 0x00, 0x0b, 0xb0, 0x0b, 0x00, 0xb0, 0xb0,
  0xb0, 0xb0, 0x00, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0x00, 0xbb, 0xbb, 0xb0, 0x00, 0xb0, 0xbb, 0xb0, 0x00, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xbb, 0xb0,
  0x0b, 0x00, 0x0b, 0xb0, 0xb0, 0xb0, 0xbb, 0xb0, 0x00, 0xb0, 0xb0, 0xb0, 0x0b, 0xb0, 0xb0, 0xb0, 0x0b, 0xb0, 0xb0, 0xb0, 0xbb, 0xb0, 0xb0, 0x00,
  0x00, 0xb0, 0xb0, 0xb0, 0x0b, 0x00, 0xb0, 0x00, 0x00, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0x00, 0xb0, 0x00,
  0xb0, 0xb0, 0xb0, 0xb0, 0x0b, 0x00, 0xb0, 0xb0, 0x00, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0x00,
  0x0b, 0x00, 0xbb, 0xb0, 0x0b, 0x00, 0x0b, 0x00, 0x00, 0xb0, 0xb0, 0xb0, 0xbb, 0xb0, 0xb0, 0xb0, 0xbb, 0xb0, 0x0b, 0xb0, 0x0b, 0x00, 0xb0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00, 0x00
};

const uint8_t uploadIco[] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
  0xf5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xf0,
  0x59, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x50,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x95, 0x11, 0x19, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x95, 0x51, 0x11, 0x11, 0x11, 0x11, 0x55, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x51, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x59, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x93, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x13, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x31, 0x11, 0x11, 0x1f, 0xff, 0xff, 0x11, 0x11, 0x11, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x11, 0x11, 0x11, 0x19, 0x99, 0x99, 0x11, 0x11, 0x11, 0x39, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x9f, 0x11, 0x11, 0x11, 0x19, 0x99, 0x99, 0x11, 0x11, 0x11, 0x19, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x91, 0x11, 0x11, 0x11, 0x19, 0x99, 0x99, 0x11, 0x11, 0x11, 0x11, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x91, 0x11, 0x11, 0x11, 0x19, 0x99, 0x99, 0x11, 0x11, 0x11, 0x11, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x91, 0x11, 0x11, 0x11, 0x19, 0x99, 0x99, 0x11, 0x11, 0x11, 0x11, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x91, 0x11, 0x11, 0xff, 0xf9, 0x99, 0x99, 0xff, 0xf1, 0x11, 0x11, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x91, 0x11, 0x11, 0x99, 0x99, 0x99, 0x99, 0x99, 0x91, 0x11, 0x11, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x91, 0x11, 0x11, 0x99, 0x99, 0x99, 0x99, 0x99, 0x91, 0x11, 0x11, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x91, 0x11, 0x11, 0x19, 0x99, 0x99, 0x99, 0x99, 0x11, 0x11, 0x1f, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x93, 0x11, 0x11, 0x11, 0x99, 0x99, 0x99, 0x91, 0x11, 0x11, 0x15, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x11, 0x11, 0x11, 0x19, 0x99, 0x99, 0x11, 0x11, 0x11, 0x19, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x51, 0x11, 0x11, 0x11, 0x99, 0x91, 0x11, 0x11, 0x11, 0x59, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x93, 0x11, 0x11, 0x11, 0x19, 0x11, 0x11, 0x11, 0x19, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0xf1, 0x11, 0x11, 0x11, 0x1f, 0xf9, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0xff, 0xff, 0xff, 0xf9, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0b, 0xb0, 0x0b, 0x00, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0x0b, 0x00, 0x0b, 0x00, 0x0b, 0xb0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xbb, 0xb0, 0xb0, 0xb0, 0xb0, 0x00, 0xb0, 0xb0, 0xb0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0x0b, 0xb0, 0xb0, 0xb0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xb0, 0xb0, 0xb0, 0xb0, 0x0b, 0x0b, 0x00, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xb0, 0xb0, 0xb0, 0xb0, 0x0b, 0x0b, 0x00, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0b, 0xb0, 0x0b, 0x00, 0x0b, 0x0b, 0x00, 0xb0, 0xb0, 0xb0, 0x0b, 0x00, 0xbb, 0xb0, 0x0b, 0xb0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t otaIco[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x90, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x99, 0x99, 0x90, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00,
  0x00, 0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00,
  0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00,
  0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00,
  0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00,
  0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00,
  0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x0b,
  0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00,
  0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00,
  0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00,
  0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00,
  0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00,
  0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbb, 0xb0, 0x0b, 0xbb, 0xbb, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x00, 0xb0, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x00, 0xb0, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x00, 0xb0, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x00, 0xb0, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x00, 0xb0, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x0b, 0xbb, 0xbb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbb, 0xb0, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t iconBin[] PROGMEM = {
  0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1c, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
  0xcc, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1c, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1c, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1c, 0x11,
  0x11, 0x11, 0x11, 0x11, 0x1c, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1c, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1c, 0x11, 0x11, 0x11,
  0x11, 0x11, 0x1c, 0x1c, 0xc1, 0x1c, 0x1c, 0xc1, 0x1c, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1c, 0x1c, 0x1c, 0x11, 0x1c, 0x1c,
  0x1c, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1c, 0x1c, 0xc1, 0x1c, 0x1c, 0x1c, 0x1c, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1c, 0x1c,
  0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x11, 0x11, 0x11,
  0x11, 0x11, 0x1c, 0x1c, 0xc1, 0x1c, 0x1c, 0x1c, 0x1c, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1c, 0x11, 0x11, 0x11, 0x11, 0x11,
  0x1c, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1c, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1c, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1c, 0x11,
  0x11, 0x11, 0x11, 0x11, 0x1c, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1c, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x11, 0x11, 0x11,
  0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11
};

struct {
  int16_t saveMenuPos;
  int16_t saveStartMenuPos;
  uint32_t crc32;
} rtcData;

uint32_t calculateCRC32inRTC(const uint8_t *data) {
  size_t length = sizeof(rtcData) - 4;
  uint32_t crc = 0xffffffff;
  while (length--) {
    uint8_t c = *data++;
    for (uint32_t i = 0x80; i > 0; i >>= 1) {
      bool bit = crc & 0x80000000;
      if (c & i) {
        bit = !bit;
      }
      crc <<= 1;
      if (bit) {
        crc ^= 0x04c11db7;
      }
    }
  }
  return crc;
}

uint8_t drawDialog() {
  char txt[] = "Press leftbutton to delete this save.";
  char b1[] = "Yes";
  char b2[] = "No";
  int16_t i, x, y;
  setColor(1);
  for (i = 30; i < 90; i++)
    drwLine(20, i, 108, i);
  setColor(8);
  drwLine(20, 30, 108, 30);
  drwLine(20, 90, 108, 90);
  drwLine(20, 30, 20, 90);
  drwLine(108, 30, 108, 90);
  x = 24;
  y = 32;
  for (i = 0; i < 37; i++) {
    putchar(txt[i], x, y);
    x += 6;
    if (x > 102) {
      x = 24;
      y += 8;
    }
  }
  for (i = 0; i < 4; i++) {
    putchar(b1[i], 24 + i * 6, 80);
  }
  for (i = 0; i < 3; i++) {
    putchar(b2[i], 80 + i * 6, 80);
  }
  redrawScreen();
  delay(400);
  while (1) {
    thiskey = 0;
    while (thiskey == 0) {
      getKey();
      delay(100);
      changeSettings();
      if (fileIsLoad)
        return 0;
    }
    if (thiskey & 4) {  //left
      return 1;
    } else
      return 0;
  }
}

void drawMenuBackground() {
  int16_t i;
  setColor(1);
  for (i = 7; i < 121; i++)
    drwLine(13, i, 115, i);
  setColor(8);
  drwLine(12, 6, 116, 6);
  drwLine(12, 121, 116, 121);
  drwLine(12, 6, 12, 121);
  drwLine(116, 6, 116, 121);
}

void drawSave(uint8_t startPos, uint8_t selectPos) {
  uint16_t pos;
  uint8_t c, i, n;
  String s_buffer;
  pos = 0;
  n = 0;
  while (pos < EEPROM_SIZE && (n - startPos < 14)) {
    if (n == selectPos)
      setColor(2);
    else
      setColor(0);
    c = EEPROM.read(pos);
    if (c == 0 || c == 0xff)
      return;
    if (n >= startPos) {
      i = 0;
      c = EEPROM.read(pos + 1);
      while (i < 12 && c != 0) {
        putchar(c, 14 + i * 6, 8 + (n - startPos) * 8);
        i++;
        c = EEPROM.read(pos + 1 + i);
      }
      c = EEPROM.read(pos);
      s_buffer = String(c);
      for (i = 0; i < s_buffer.length(); i++) {
        putchar(s_buffer[i], 100 + i * 6, 8 + (n - startPos) * 8);
      }
    }
    n++;
    pos += c;
  }
}

uint8_t getSaveLength() {
  uint16_t pos = 0;
  uint8_t n = 0;
  uint8_t c;
  while (pos < EEPROM_SIZE) {
    c = EEPROM.read(pos);
    if (c == 0 || c == 0xff)
      return n;
    pos += c;
    n++;
  }
  return n;
}

void deleteSave(uint8_t num, uint16_t end) {
  uint16_t i, pos = 0;
  uint8_t n = 0;
  uint8_t c;
  while (pos < EEPROM_SIZE && n != num) {
    c = EEPROM.read(pos);
    pos += c;
    n++;
  }
  c = EEPROM.read(pos);
  for (i = pos + c; i < end; i++) {
    EEPROM.write(i - c, EEPROM.read(i));
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}

void saveManager() {
  uint8_t pos, listLength;
  drawMenuBackground();
  drawSave(0, 0);
  redrawScreen();
  pos = 0;
  listLength = getSaveLength();
  delay(400);
  while (1) {
    thiskey = 0;
    while (thiskey == 0) {
      getKey();
      delay(100);
      changeSettings();
      if (fileIsLoad)
        return;
    }
    if (thiskey & 128 || thiskey & 32) {
      return;
    } else if (thiskey & 2) {  //down
      if (pos < listLength - 1) {
        pos++;
        drawMenuBackground();
        drawSave(pos, pos);
        redrawScreen();
      }
    } else if (thiskey & 1) {  //up
      if (pos > 0) {
        pos--;
        drawMenuBackground();
        drawSave(pos, pos);
        redrawScreen();
      }
    } else if (thiskey & 16) {  //ok
      if (drawDialog()) {
        deleteSave(pos, findEndData());
      }
      drawMenuBackground();
      drawSave(pos, pos);
      redrawScreen();
    }
  }
}

void drawIco(const uint8_t *a, int16_t x, int16_t y, int16_t w, int16_t h) {
  uint8_t p, color;
  int i = 0;
  for (int16_t yi = 0; yi < h; yi++)
    for (int16_t xi = 0; xi < w; xi++) {
      p = pgm_read_byte(a + i);
      color = (p & 0xf0) >> 4;
      if (color > 0) {
        setPix(xi + x, yi + y, color);
      }
      xi++;
      color = p & 0x0f;
      if (color > 0) {
        setPix(xi + x, yi + y, color);
      }
      i++;
    }
}

void softwareMenu() {
  uint8_t pos = 0, x, y;
  delay(400);
  while (1) {
    x = (pos % 2) * 50 + 14;
    y = (pos / 2) * 58 + 11;
    drawMenuBackground();
    setColor(10);
    fllRect(x, y, x + 50, y + 50);
    drawIco(saveIco, 16, 12, 48, 48);
    drawIco(uploadIco, 66, 12, 48, 48);
    drawIco(otaIco, 16, 68, 48, 48);
    redrawScreen();
    thiskey = 0;
    while (thiskey == 0) {
      getKey();
      delay(100);
      changeSettings();
    }
    if (thiskey & 2) {  //down
      if (pos == 0) {
        pos = 2;
      }
    } else if (thiskey & 1) {  //up
      if (pos == 2) {
        pos = 0;
      }
    } else if (thiskey & 4) {  //left
      if (pos == 1) {
        pos = 0;
      }
    } else if (thiskey & 8) {  //right
      if (pos == 0) {
        pos = 1;
      }
    }
    if (thiskey & 16) {
      if (pos == 0) {
        saveManager();
      } else if (pos == 1) {
        memoryFree();
        startServer();
      }
      return;
    }
    if (thiskey & 32) {
      return;
    }
  }
}

void drawVersionInFileList() {
  //Print version
  tft.setTextColor(TFT_DARKGREY);
  tft.setCursor(20, SCREEN_REAL_HEIGHT - 8);
  tft.print(F(BUILD_VERSION));
}

void fileList(String path) {
  fs::Dir dir = LittleFS.openDir(path);
  char s[32];
  char thisF[32];
  int16_t lst = 0;
  int16_t pos;
  int16_t startpos = 0;
  int16_t fileCount = 1;
  int16_t skip = 0;
  uint8_t i, b;
  ESP.rtcUserMemoryRead(0, (uint32_t *)&rtcData, sizeof(rtcData));
  if (rtcData.crc32 != calculateCRC32inRTC((uint8_t *)&rtcData)) {
    rtcData.saveMenuPos = 0;
    rtcData.saveStartMenuPos = 0;
    rtcData.crc32 = calculateCRC32inRTC((uint8_t *)&rtcData);
    ESP.rtcUserMemoryWrite(0, (uint32_t *)&rtcData, sizeof(rtcData));
  }
  setClip(0, 0, 128, 128);
  pos = rtcData.saveMenuPos;
  startpos = rtcData.saveStartMenuPos;
  display_init();
  setBgColor(0);
  setColor(1);
  tft.fillScreen(0x0000);
  for (i = 0; i < 192; i++)
    writeMem(i + 1024 + 192, pgm_read_byte_near(iconBin + i));
  setImageSize(1);
  while (dir.next()) {
    fs::File entry = dir.openFile("r");
    entry.close();
    fileCount++;
  }
  if (startpos > fileCount)
    startpos = 0;
  Serial.print(F("find "));
  Serial.print(fileCount);
  Serial.println(F(" files"));
  while (1) {
    clearScr(0);
    skip = startpos - 1;
    if (skip < 0)
      skip = 0;
    lst = 1;
    dir = LittleFS.openDir(path);
    setColor(8);
    for (i = 1; i < 17; i++)
      drwLine(2, (pos - startpos) * 17 + i, 124, (pos - startpos) * 17 + i);
    setColor(1);
    if (startpos == 0) {
      putString(ROM_NAME, lst * 17 - 16);
      loadRomIco();
      drawImg(1024, 0, lst * 17 - 16, 24, 16);
      lst++;
    }
    while (dir.next() && lst < 8) {
      fs::File entry = dir.openFile("r");
      if (skip > 0) {
        skip--;
      } else {
        strcpy(s, entry.name());
        if (lst + startpos - 1 == pos)
          strcpy(thisF, entry.name());
        putString(s, lst * 17 - 16);
        i = 0;
        while (i < 28 && s[i] != '.')
          i++;
        i++;
        if (s[i] == 'l' && s[i + 1] == 'g' && s[i + 2] == 'e') {
          entry.seek(3, SeekSet);
          if (entry.available())
            b = (uint8_t)entry.read();
          if (b & 0x2) {
            entry.seek(5, SeekSet);
            for (i = 0; i < 192; i++)
              if (entry.available())
                writeMem(i + 1024, (uint8_t)entry.read());
            drawImg(1024, 0, lst * 17 - 16, 24, 16);
          } else
            drawImg(1024 + 192, 0, lst * 17 - 16, 24, 16);
        } else if (s[i] == 'b' && s[i + 1] == 'i' && s[i + 2] == 'n')
          drawImg(1024 + 192, 0, lst * 17 - 16, 24, 16);
        lst++;
      }
      entry.close();
    }
    if (lst + startpos - 1 < pos) {
      if (fileCount > pos)
        startpos++;
      else
        pos--;
    } else if (startpos > pos) {
      startpos = pos;
    }
    redrawScreen();
    drawVersionInFileList();
    delay(200);
    getKey();
    while (thiskey == 0) {
      getKey();
      delay(100);
      changeSettings();
      if (fileIsLoad)
        return;
    }
    if (thiskey & 16) {  //ok
      rtcData.saveMenuPos = pos;
      rtcData.saveStartMenuPos = startpos;
      rtcData.crc32 = calculateCRC32inRTC((uint8_t *)&rtcData);
      ESP.rtcUserMemoryWrite(0, (uint32_t *)&rtcData, sizeof(rtcData));
      cpuInit();
      i = 0;
      while (i < 28 && thisF[i] != '.')
        i++;
      i++;
      setLoadedFileName(thisF);
      if (startpos == pos && pos == 0)
        loadRom();
      else if (thisF[i] == 'b' && thisF[i + 1] == 'i' && thisF[i + 2] == 'n')
        loadBinFromSPIFS(thisF);
      else if (thisF[i] == 'l' && thisF[i + 1] == 'g' && thisF[i + 2] == 'e')
        loadLgeFromSPIFS(thisF);
      return;
    } else if (thiskey & 2) {  //down
      if (pos < fileCount - 1) {
        pos++;
      } else {
        pos = 0;
        startpos = 0;
      }
      if (pos - startpos > 5) {
        startpos++;
        setColor(0);
        for (int8_t i = 0; i < 8; i++) {
          drwLine(0, 0, 127, 0);
          drwLine(0, 1, 127, 1);
          scrollScreen(0, 1);
          scrollScreen(0, 1);
          redrawScreen();
        }
      }
    } else if (thiskey & 1) {  //up
      if (pos > 0) {
        pos--;
      } else {
        pos = fileCount - 1;
        startpos = (fileCount - 6 >= 0) ? fileCount - 6 : 0;
      }
      if (pos - startpos < 0) {
        startpos--;
        setColor(0);
        for (int8_t i = 0; i < 8; i++) {
          scrollScreen(0, 3);
          scrollScreen(0, 3);
          drwLine(0, 0, 127, 0);
          drwLine(0, 1, 127, 1);
          redrawScreen();
          drawVersionInFileList();
        }
      }
    }
    if (thiskey & 32) {  //B
      softwareMenu();
      delay(400);
    }
    if (thiskey & 128) {  //select
      saveManager();
      delay(400);
    }
  }
}

void loadBinFromSPIFS(char fileName[]) {
  int i;
  for (i = 0; i < RAM_SIZE; i++)
    writeMem(i, 0);
  fs::File f = LittleFS.open(fileName, "r");
  if (f.size() < RAM_SIZE)
    for (i = 0; i < f.size(); i++) {
      writeMem(i, (uint8_t)f.read());
    }
  Serial.print(F("loaded "));
  Serial.print(i);
  Serial.println(F(" byte"));
  Serial.print(F("free heap "));
  Serial.println(system_get_free_heap_size());
  f.close();  //Close file
}

void loadLgeFromSPIFS(char fileName[]) {
  int n, j, i = 0;
  uint8_t b, l;
  int16_t length, position, point;
  for (i = 0; i < RAM_SIZE; i++)
    writeMem(i, 0);
  fs::File f = LittleFS.open(fileName, "r");
  if ((char)f.read() == 'l' && (char)f.read() == 'g' && (char)f.read() == 'e') {
    l = (uint8_t)f.read();
  } else
    return;
  n = (uint8_t)f.read();
  //Serial.print(F("offset "));
  //Serial.print(n);
  f.seek(n, SeekSet);
  n = 0;
  while (f.available()) {
    b = (uint8_t)f.read();
    if ((b & 128) == 0) {
      length = ((b & 127) << 8) + (uint8_t)f.read();
      for (j = 0; j < length; j++) {
        if (n < RAM_SIZE)
          writeMem(n, (uint8_t)f.read());
        n++;
      }
    } else {
      length = (b & 127) >> 1;
      position = (((b & 1) << 8) + (uint8_t)f.read());
      point = n - position;
      for (j = 0; j < length; j++) {
        if (n < RAM_SIZE && point + j < RAM_SIZE)
          writeMem(n, readMem(point + j));
        n++;
      }
    }
  }
  Serial.print(F("loaded "));
  Serial.print(n);
  Serial.println(F(" byte"));
  Serial.print(F("free heap "));
  Serial.println(system_get_free_heap_size());
  f.close();  //Close file
}
