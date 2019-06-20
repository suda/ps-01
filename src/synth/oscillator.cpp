#include "oscillator.h"

Oscillator::Oscillator() {
    generateTriangleWave();
    generateSawtoothWave();
}

int16_t Oscillator::getSample() {
    float delta = (_frequency*WAVE_TABLE_SIZE)/float(SAMPLERATE_HZ);
    uint16_t pos = uint16_t(_clock*delta) % WAVE_TABLE_SIZE;
    switch (_waveform) {
    case WF_SAWTOOTH:
        return sawtoothWave[pos];
        break;
    case WF_TRIANGLE:
        return triangleWave[pos];
        break;
    
    default:
        return 0;
        break;
    }
}

void Oscillator::clock() {
    _clock++;
}

void Oscillator::setWaveform(Waveform waveform) {
    _waveform = waveform;
}

void Oscillator::setFrequency(float frequency) {
    _frequency = frequency;
}

void Oscillator::generateTriangleWave() {
    float delta = float(AMPLITUDE)/float(WAVE_TABLE_SIZE);
    for (int i=0; i<WAVE_TABLE_SIZE/2; ++i) { 
        triangleWave[i] = -(AMPLITUDE/2)+delta*i;
    }
    for (int i=WAVE_TABLE_SIZE/2; i<WAVE_TABLE_SIZE; ++i) { 
        triangleWave[i] = (AMPLITUDE/2)-delta*(i-WAVE_TABLE_SIZE/2);
    } 
}

void Oscillator::generateSawtoothWave() {
    float delta = float(AMPLITUDE)/float(WAVE_TABLE_SIZE);
    for (int i=0; i<WAVE_TABLE_SIZE; ++i) {
        sawtoothWave[i] = -(AMPLITUDE/2)+delta*i; 
    }
}

void Oscillator::debug() {
    Log.trace("Clock: %d Sample: %d Freq: %f", _clock, getSample(), _frequency);
}