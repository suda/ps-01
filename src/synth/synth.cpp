#include "synth.h"

Synth::Synth() {
}

void Synth::begin() {
    voices[0].setFrequency(440.0);
    setupSoundOutput();
}

void Synth::setupSoundOutput() {
    attachInterruptDirect(I2S_IRQn, nrfx_i2s_irq_handler);

    nrfx_i2s_config_t const config = {
        .sck_pin = I2S_PIN_SCK,
        .lrck_pin = I2S_PIN_LRCK,
        .mck_pin = NRFX_I2S_PIN_NOT_USED,
        .sdout_pin = I2S_PIN_SDOUT,
        .sdin_pin = NRFX_I2S_PIN_NOT_USED,
        .irq_priority = NRFX_I2S_CONFIG_IRQ_PRIORITY,
        .mode = NRF_I2S_MODE_MASTER,
        .format = NRF_I2S_FORMAT_I2S,
        .alignment = NRF_I2S_ALIGN_LEFT,
        .sample_width = NRF_I2S_SWIDTH_16BIT,
        .channels = NRF_I2S_CHANNELS_STEREO,
        .mck_setup = NRF_I2S_MCK_32MDIV11,
        .ratio = NRF_I2S_RATIO_64X
    };

    i2sBuffersA.p_tx_buffer = (uint32_t*)bufferA;
    i2sBuffersB.p_tx_buffer = (uint32_t*)bufferB;

    nrfx_i2s_init(&config, dataHandlerCb);
    nrfx_i2s_start(&i2sBuffersA, sizeof(bufferA) / sizeof(uint32_t), 0);
}

void Synth::dataHandler(uint32_t status) {
    if (status == NRFX_I2S_STATUS_NEXT_BUFFERS_NEEDED) {
        nrfx_i2s_next_buffers_set(usingSecondBuffer ? &i2sBuffersB : &i2sBuffersA);
        usingSecondBuffer = !usingSecondBuffer;
        fillBuffer();
    }
}

void Synth::dataHandlerCb(nrfx_i2s_buffers_t const *p_released, uint32_t status) {
    auto self = Synth::instance();
    self->dataHandler(status);
}
uint16_t c = 0;
void Synth::fillBuffer() {
    for (uint16_t i = 0; i < BUFF_SIZE; i++) {
        int16_t sample = voices[0].getSample();

        if (usingSecondBuffer) {
            bufferA[i*2] = sample;
            bufferA[i*2+1] = sample;
        } else {
            bufferB[i*2] = sample;
            bufferB[i*2+1] = sample;
        }
        voices[0].clock();
        c++;
    }
}

void Synth::debug() {
    voices[0].setFrequency(493.88);
    voices[0].debug();
}