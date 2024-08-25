#ifndef SOUND_HPP
#define SOUND_HPP

#include <Arduino.h>  // For Arduino specific functions like tone() and noTone()
#include "settings.h"

// Define constants
#define OCTAVE_OFFSET 0

// Define RTTTL structure
struct RTTTL {
    uint16_t address;
    uint16_t position;
    uint16_t startposition;
    uint8_t loop;
    uint8_t play;
    uint8_t default_dur;
    uint8_t default_oct;
    uint16_t bpm;
    uint32_t wholenote;
    uint16_t this_tone;
    int16_t delay;
    uint8_t isPlayed;
};

// Define PLAY_TONE structure
struct PLAY_TONE {
    uint16_t freq;
    int16_t time;
};

// Declare external variables
extern struct RTTTL rtttl;
extern struct PLAY_TONE play_tone;

// Function prototypes
uint8_t loadRtttl();
inline void addTone(uint16_t f, uint16_t t);
void setRtttlAddress(uint16_t adr);
void setRtttlLoop(uint8_t loop);
void setRtttlPlay(uint8_t play);
inline void updateRtttl();
int playRtttl();

#endif // SOUND_HPP
