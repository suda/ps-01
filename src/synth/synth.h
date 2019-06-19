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

#define SAMPLERATE_HZ 44100
#define BUFF_SIZE 1024

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

  Voice getVoice(int voiceNumber);
protected:
  Synth();
private:
  void setupSoundOutput();
  int16_t bufferA[BUFF_SIZE*2] = {};
  int16_t bufferB[BUFF_SIZE*2] = {};
  nrfx_i2s_buffers_t i2sBuffersA;
  nrfx_i2s_buffers_t i2sBuffersB;
  bool usingSecondBuffer;

  void dataHandler(uint32_t status);
  static void dataHandlerCb(nrfx_i2s_buffers_t const *p_released, uint32_t status);
};

#endif /* SYNTH_H_ */
