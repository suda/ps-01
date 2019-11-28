#ifndef TYPES_H_
#define TYPES_H_

#pragma once

#if defined(PARTICLE)
  #include "Particle.h"
  #define LOGGER(...) Serial.printf(__VA_ARGS__);
#else
  #include <stdint.h>
  #include <stdio.h>
  #define LOGGER(...) printf(__VA_ARGS__, "\n");
#endif

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

struct Store {
    uint8_t volume;
    uint32_t tick;

    // ScaleTestPage
    uint32_t stLastTick;
    uint8_t stCurrentNote;
    Waveform stCurrentWaveform = WF_TRIANGLE;
};

#define BUFFER_SIZE     1024
#define VOICES_COUNT    3

// #define SAMPLERATE_44K
// #define SAMPLERATE_22K
#define SAMPLERATE_16K
// #define SAMPLERATE_11K

#ifdef SAMPLERATE_44K
  #define SAMPLERATE_HZ   44100
  #if defined(PARTICLE)
   // Effective sampling rate of 44.44444375kHz
    #define I2S_MCK NRF_I2S_MCK_32MDIV15
    #define I2S_RATIO NRF_I2S_RATIO_48X
  #endif
#endif

#ifdef SAMPLERATE_22K
  #define SAMPLERATE_HZ   22050
  #if defined(PARTICLE)
    // Effective sampling rate of 21.5053770833kHz
    #define I2S_MCK NRF_I2S_MCK_32MDIV31
    #define I2S_RATIO NRF_I2S_RATIO_48X
  #endif
#endif

#ifdef SAMPLERATE_16K
  #define SAMPLERATE_HZ   16129
  #if defined(PARTICLE)
    // Effective sampling rate of 16.1290328125kHz
    #define I2S_MCK NRF_I2S_MCK_32MDIV31
    #define I2S_RATIO NRF_I2S_RATIO_64X
  #endif
#endif

#ifdef SAMPLERATE_11K
  #define SAMPLERATE_HZ   11025
  #if defined(PARTICLE)
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

#if defined(PARTICLE)
  #define I2S_PIN_SCK    (NRF_GPIO_PIN_MAP(0, 28)) // A2
  #define I2S_PIN_LRCK   (NRF_GPIO_PIN_MAP(0, 3)) // A0
  #define I2S_PIN_SDOUT  (NRF_GPIO_PIN_MAP(0, 4)) // A1

  #define ENCODER_INT_PIN D2
  #define KEYPAD_INT_PIN  D3
  #define BUTTON_INT_PIN  D4

  #define TFT_DC A3
  #define TFT_CS A5
  #define TFT_MOSI MOSI
  #define TFT_CLK SCK
  #define TFT_RST A4
  #define TFT_MISO MISO
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

#define CORNER_SIZE 4

#define COLOR_WHITE            0xFFFF
#define COLOR_BLACK            0x0000
#define COLOR_BG               0x2A28
#define COLOR_BLUE             0x663F
#define COLOR_BLUE_SHADOW      0x3BF8
#define COLOR_GREEN            0x5F92
#define COLOR_GREEN_SHADOW     0x34EF
#define COLOR_PURPLE           0xCC9E
#define COLOR_PURPLE_SHADOW    0x82B7
#define COLOR_RED              0xF22B
#define COLOR_RED_SHADOW       0x984A
#define COLOR_ORANGE           0xFD20
#define COLOR_ORANGE_SHADOW    0xD240
#define COLOR_GRAY             0xB619
#define COLOR_GRAY_SHADOW      0x6BF1
#define COLOR_DIALOG           0xEFDF
#define COLOR_DIALOG_SHADOW    0xA6BA

#define BIT_SET(a, b) ((a) |= (1ULL<<(b)))
#define BIT_CLEAR(a, b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a, b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a, b) (!!((a) & (1ULL<<(b)))) 

#endif /* TYPES_H_ */