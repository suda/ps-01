#ifndef TYPES_H_
#define TYPES_H_

#pragma once

typedef enum {
    ADSR_ATTACK  = 0,
    ADSR_DECAY   = 1,
    ADSR_SUSTAIN = 2,
    ADSR_RELEASE = 3,
    ADSR_IDLE    = 4
} ADSRState;

typedef enum {
    WF_TEST     = 0,
    WF_PULSE    = 1,
    WF_SAWTOOTH = 2,
    WF_TRIANGLE = 3,
    WF_NOISE    = 4,
    WF_NO_WAVE  = 5
} Waveform;

typedef enum {
    CH_LEFT  = 1,
    CH_RIGHT = 2,
    CH_BOTH  = 3
} Channel;

#define BUFFER_SIZE     1024
#define VOICES_COUNT    3
#define SAMPLERATE_HZ   44100
#define AMPLITUDE       ((1<<16)-1)
// #define AMPLITUDE       ((1<<12)-1)
#define WAVE_TABLE_SIZE 256

#define C4_HZ 261.63
#define D4_HZ 293.66
#define E4_HZ 329.63
#define F4_HZ 349.23
#define G4_HZ 392.00
#define A4_HZ 440.00
#define B4_HZ 493.88
#define C5_HZ 523.25

#ifndef PARTICLE
#include <stdint.h>
#endif

#endif /* TYPES_H_ */