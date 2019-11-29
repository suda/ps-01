#pragma once

#include "../util/types.h"
#if defined(PARTICLE)
#undef SCK
#include "nrf_gpio.h"
#include <nrfx_i2s.h>
#else
#include <string.h>
#include <SDL.h>
#endif

#include "voice.h"

class Synth {
public:
  static Synth* instance() {
    static Synth s;
    return &s;
  }
  void begin();

  Voice voices[VOICES_COUNT];
  void debug();
#ifndef PARTICLE
  void playBuffer();
#endif
protected:
  Synth();
private:
  int16_t bufferA[BUFFER_SIZE*2] = {};
  int16_t bufferB[BUFFER_SIZE*2] = {};
  // Which buffer is currently used by the DMA?
  bool usingSecondBuffer = false;

  void setupSoundOutput();
#if defined(PARTICLE)
  // I2S specific definitions
  nrfx_i2s_buffers_t i2sBuffersA = {
      .p_rx_buffer = 0,
      .p_tx_buffer = 0
  };
  nrfx_i2s_buffers_t i2sBuffersB = {
      .p_rx_buffer = 0,
      .p_tx_buffer = 0
  };
  void dataHandler(uint32_t status);
  static void dataHandlerCb(nrfx_i2s_buffers_t const *p_released, uint32_t status);
#else
  FILE *writehandle = NULL;
  static void audioCallback(void *userdata, Uint8 *stream, int len);
#endif

  void fillBuffer();
  int16_t getChannelSample(Channel channel);
};