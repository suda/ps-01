#ifndef TYPES_H_
#define TYPES_H_

#pragma once

typedef enum {
    ADSR_IDLE    = 0,
    ADSR_ATTACK  = 1,
    ADSR_DECAY   = 2,
    ADSR_SUSTAIN = 3,
    ADSR_RELEASE = 4
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

// #define SAMPLERATE_44K
// #define SAMPLERATE_22K
#define SAMPLERATE_16K
// #define SAMPLERATE_11K

#ifdef SAMPLERATE_44K
#define SAMPLERATE_HZ   44100
#ifdef PARTICLE
// Effective sampling rate of 44.44444375kHz
#define I2S_MCK NRF_I2S_MCK_32MDIV15
#define I2S_RATIO NRF_I2S_RATIO_48X
#endif
#endif

#ifdef SAMPLERATE_22K
#define SAMPLERATE_HZ   22050
#ifdef PARTICLE
// Effective sampling rate of 21.5053770833kHz
#define I2S_MCK NRF_I2S_MCK_32MDIV31
#define I2S_RATIO NRF_I2S_RATIO_48X
#endif
#endif

#ifdef SAMPLERATE_16K
#define SAMPLERATE_HZ   16129
#ifdef PARTICLE
// Effective sampling rate of 16.1290328125kHz
#define I2S_MCK NRF_I2S_MCK_32MDIV31
#define I2S_RATIO NRF_I2S_RATIO_64X
#endif
#endif

#ifdef SAMPLERATE_11K
#define SAMPLERATE_HZ   11025
#ifdef PARTICLE
// Effective sampling rate of 10.8843535714kHz
#define I2S_MCK NRF_I2S_MCK_32MDIV15
#define I2S_RATIO NRF_I2S_RATIO_192X
#endif
#endif

// Number of clock cycles for one milisecond
#define ONE_MS          SAMPLERATE_HZ / 1000
#define AMPLITUDE       ((1<<16)-1)
// #define AMPLITUDE       ((1<<12)-1)
#define WAVE_TABLE_SIZE 256

#ifdef PARTICLE
#define I2S_PIN_SCK    (NRF_GPIO_PIN_MAP(0, 28)) // A2
#define I2S_PIN_LRCK   (NRF_GPIO_PIN_MAP(0, 3)) // A0
#define I2S_PIN_SDOUT  (NRF_GPIO_PIN_MAP(0, 4)) // A1

#define ENCODER_INT_PIN D2

#define KEYPAD_INT_PIN  D3
#else
#include <stdint.h>
#endif

#define C4_HZ  261.63
#define C4S_HZ 277.18
#define D4_HZ  293.66
#define D4S_HZ 311.13
#define E4_HZ  329.63
#define F4_HZ  349.23
#define F4S_HZ 370.00
#define G4_HZ  392.00
#define G4S_HZ 415.30
#define A4_HZ  440.00
#define A4S_HZ 466.16
#define B4_HZ  493.88
#define C5_HZ  523.25

#define BIT_SET(a, b) ((a) |= (1ULL<<(b)))
#define BIT_CLEAR(a, b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a, b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a, b) (!!((a) & (1ULL<<(b)))) 

#endif /* TYPES_H_ */