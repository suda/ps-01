#pragma once

#include "../util/types.h"
#if defined(PARTICLE)
#undef SCK
#include <nrfx_i2s.h>
#include "nrf_gpio.h"
#else
#include <SDL.h>
#include <string.h>
#endif

#include "voice.h"

class Synth {
   public:
    static Synth* instance() {
        static Synth s;
        return &s;
    }
    Voice voices[VOICES_COUNT];

    void begin();
    void setupAllVoices(Waveform waveform, uint16_t attack, uint16_t decay,
                        uint8_t sustain, uint16_t release, uint16_t pulseWidth);
    void debug();
#ifndef PARTICLE
    void playBuffer();
#endif
   protected:
    Synth();

   private:
    int16_t bufferA[BUFFER_SIZE * 2] = {};
    int16_t bufferB[BUFFER_SIZE * 2] = {};
    // Which buffer is currently used by the DMA?
    bool usingSecondBuffer = false;

    void setupSoundOutput();
#if defined(PARTICLE)
    // I2S specific definitions
    nrfx_i2s_buffers_t i2sBuffersA = {.p_rx_buffer = 0, .p_tx_buffer = 0};
    nrfx_i2s_buffers_t i2sBuffersB = {.p_rx_buffer = 0, .p_tx_buffer = 0};
    void dataHandler(uint32_t status);
    static void dataHandlerCb(nrfx_i2s_buffers_t const* p_released,
                              uint32_t status);
#else
    FILE *writehandle = NULL;
    static void audioCallback(void *userdata, Uint8 *stream, int len);
#endif

    void fillBuffer();
    int16_t getChannelSample(Channel channel);
};