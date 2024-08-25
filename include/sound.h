#ifndef SOUND_HPP
#define SOUND_HPP

#include <Arduino.h> // For Arduino specific functions like tone() and noTone()
#include "settings.h"

#define OCTAVE_OFFSET 0

// Define RTTTL structure
struct RTTTL
{
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

struct RTTTL rtttl;

#define NEXT_CHAR          \
    rtttl.startposition++; \
    c = (char)readMem(rtttl.startposition);
#define NEXT_CHAR_IN_P \
    rtttl.position++;  \
    c = (char)readMem(rtttl.startposition + rtttl.position);

struct PLAY_TONE
{
    uint16_t freq;
    int16_t time;
};

struct PLAY_TONE play_tone;

const int notes[] PROGMEM = {0,
                             262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,
                             523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,
                             1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
                             2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951};

unsigned int millisec = (unsigned int)millis();

// Function prototypes
uint8_t loadRtttl();
void setRtttlAddress(uint16_t adr);
void setRtttlLoop(uint8_t loop);
void setRtttlPlay(uint8_t play);
int playRtttl();
inline void updateRtttl()
{
    if (rtttl.delay > 0)
        rtttl.delay--;
    if (play_tone.time > 0)
        play_tone.time--;
    // play single tone
    if (play_tone.time > 0)
    {
        if (rtttl.delay <= 0)
        {
            noTone(SOUNDPIN);
            tone(SOUNDPIN, play_tone.freq, 128);
            rtttl.isPlayed = 0;
            return;
        }
        if (play_tone.time & 1)
        {
            noTone(SOUNDPIN);
            tone(SOUNDPIN, play_tone.freq, 128);
            rtttl.isPlayed = 0;
            return;
        }
    }
    // player
    if (rtttl.play == 0)
    {
        return;
    }
    if (rtttl.delay > 0)
    {
        if (!rtttl.isPlayed)
        {
            rtttl.isPlayed = 1;
            noTone(SOUNDPIN);
            tone(SOUNDPIN, rtttl.this_tone, rtttl.delay);
        }
        return;
    }
}

inline void addTone(uint16_t f, uint16_t t)
{
    play_tone.freq = f;
    play_tone.time = t;
}

#endif // SOUND_HPP
