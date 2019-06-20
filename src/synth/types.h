#ifndef TYPES_H_
#define TYPES_H_

#pragma once

typedef enum {
    ATTACK  = 0,
    DECAY   = 1,
    SUSTAIN = 2,
    RELEASE = 3,
    IDLE    = 4
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
    BOTH  = 0,
    LEFT  = 1,
    RIGHT = 2
} Channel;

#endif /* TYPES_H_ */