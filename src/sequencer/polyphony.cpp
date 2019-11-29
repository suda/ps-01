#include "polyphony.h"

Polyphony::Polyphony() {}

bool Polyphony::startFrequency(float frequency) {
    int8_t idx = _getFrequencyIndex(frequency);
    if (idx > -1) {
        // It's already playing
        return true;
    }
    idx = _getAvailableIndex();
    if (idx == -1) {
        // There are no more voices to use
        return false;
    }
    Synth::instance()->voices[idx].setFrequency(frequency);
    Synth::instance()->voices[idx].setGate(true);
    _voices[idx] = frequency;
    return true;
}

bool Polyphony::stopFrequency(float frequency) {
    int8_t idx = _getFrequencyIndex(frequency);
    if (idx < 0) {
        // It wasn't playing
        return false;
    }
    Synth::instance()->voices[idx].setGate(false);
    _voices[idx] = 0;
    return true;
}

int8_t Polyphony::_getFrequencyIndex(float frequency) {
    for (uint8_t i = 0; i < VOICES_COUNT; i++) {
        if (_voices[i] == frequency) {
            return i;
        }
    }
    // This frequency isn't playing
    return -1;
}

int8_t Polyphony::_getAvailableIndex() {
    for (uint8_t i = 0; i < VOICES_COUNT; i++) {
        if (_voices[i] == 0) {
            return i;
        }
    }
    // All voices are used
    return -1;
}