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

#define BUFF_SIZE       1024
#define VOICES_COUNT    3
#define SAMPLERATE_HZ   44100
#define AMPLITUDE       ((1<<15)-1)
// #define AMPLITUDE       ((1<<12)-1)
#define WAVE_TABLE_SIZE 256

#ifndef PARTICLE
#include <stdint.h>
#endif

#endif /* TYPES_H_ */