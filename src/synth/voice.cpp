#include "voice.h"

Voice::Voice() {}

void Voice::setWaveform(Waveform waveform) {
    oscillator.setWaveform(waveform);
}

void Voice::setFrequency(float frequency) {
    oscillator.setFrequency(frequency);
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