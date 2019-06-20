#ifndef SYNTH_H_
#define SYNTH_H_

#pragma once

#if defined(PARTICLE)
#include "Particle.h"
#undef SCK
#include "nrf_gpio.h"
#include <nrfx_i2s.h>
#endif

#include "voice.h"

#define BUFF_SIZE      1024
#define VOICES_COUNT   3

#define I2S_PIN_SCK    (NRF_GPIO_PIN_MAP(0, 30))
#define I2S_PIN_LRCK   (NRF_GPIO_PIN_MAP(0, 31))
#define I2S_PIN_SDOUT  (NRF_GPIO_PIN_MAP(1, 15))

class Synth {
public:
  static Synth* instance() {
    static Synth s;
    return &s;
  }
  void begin();

  Voice voices[VOICES_COUNT];
  void debug();
protected:
  Synth();
private:
  int16_t bufferA[BUFF_SIZE*2] = {};
  int16_t bufferB[BUFF_SIZE*2] = {};
  // Which buffer is currently used by the DMA?
  bool usingSecondBuffer = false;

  void setupSoundOutput();
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

  void fillBuffer();
};

#endif /* SYNTH_H_ */
