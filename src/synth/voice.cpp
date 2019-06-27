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

void Voice::setADSR(uint16_t attack, uint16_t decay, uint8_t sustain, uint16_t release) {
    adsr.setAttack(attack);
    adsr.setDecay(decay);
    adsr.setSustain(sustain);
    adsr.setRelease(release);
}

void Voice::setGate(bool gate) {
    adsr.setGate(gate);
}

void Voice::setChannel(Channel channel) {
    _channel = channel;
}

bool Voice::isAudibleInChannel(Channel channel) {
    return (_channel == CH_BOTH) || (_channel == channel);
}

int16_t Voice::getSample() {
    int16_t sample = oscillator.getSample();
    sample = adsr.apply(sample);
    return sample;
}

void Voice::clock() {
    _clock++;
    oscillator.clock();
    adsr.clock();
}

void Voice::debug() {
    // oscillator.debug();
}