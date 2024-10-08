#include <Arduino.h>
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
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00, 0x00};

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
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

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
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbb, 0xb0, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

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
    0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11};
