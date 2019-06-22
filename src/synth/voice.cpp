#include "voice.h"

Voice::Voice() {}

void Voice::setWaveform(Waveform waveform) {
    oscillator.setWaveform(waveform);
}

void Voice::setFrequency(float frequency) {
    oscillator.setFrequency(frequency);
}

void Voice::setPulseWidth(uint16_t pulseWidth) {
    oscillator.setPulseWidth(pulseWidth);
}

int16_t Voice::getSample() {
    return oscillator.getSample();
}

void Voice::clock() {
    _clock++;
    oscillator.clock();
}

void Voice::debug() {
    // oscillator.debug();
}