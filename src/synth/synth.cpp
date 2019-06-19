#include "synth.h"

int16_t sine_table[] = { 0, 0, 23170, 23170, 32767, 32767, 23170, 23170, 0, 0, -23170, -23170, -32768, -32768, -23170, -23170};
nrfx_i2s_buffers_t buffers = {
    .p_rx_buffer = 0,
    .p_tx_buffer = (uint32_t*)sine_table
};

// int16_t Synth::bufferA[BUFF_SIZE*2] = {};
// int16_t Synth::bufferB[BUFF_SIZE*2] = {};
// bool Synth::usingSecondBuffer = false;

Synth::Synth() {
}

void Synth::begin() {
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

    i2sBuffersA = {
        .p_rx_buffer = 0,
        .p_tx_buffer = (uint32_t*)bufferA
    };
    i2sBuffersB = {
        .p_rx_buffer = 0,
        .p_tx_buffer = (uint32_t*)bufferB
    };

    nrfx_i2s_init(&config, dataHandlerCb);
    nrfx_i2s_start(&i2sBuffersA, sizeof(bufferA) / sizeof(uint32_t), 0);
}

void Synth::dataHandler(uint32_t status) {
    if (status == NRFX_I2S_STATUS_NEXT_BUFFERS_NEEDED) {
        nrfx_i2s_next_buffers_set(usingSecondBuffer ? &i2sBuffersB : &i2sBuffersA);
    }
}

void Synth::dataHandlerCb(nrfx_i2s_buffers_t const *p_released, uint32_t status) {
    auto self = Synth::instance();
    self->dataHandler(status);
}