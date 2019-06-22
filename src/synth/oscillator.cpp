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
    case WF_PULSE:
        return pulseWave[pos];
        break;
    case WF_NOISE:
        return (int16_t)(AMPLITUDE*((frannor()+1.0)/2.0));
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

void Oscillator::setPulseWidth(uint16_t pulseWidth) {
    _pulseWidth = pulseWidth;
    generatePulseWave();
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

void Oscillator::generatePulseWave() {
    for (int i=0; i<WAVE_TABLE_SIZE; ++i) {
        pulseWave[i] = i * float((1 << 16) / WAVE_TABLE_SIZE) <= _pulseWidth ? AMPLITUDE : 0;
    }
    int rows = 16;
    for (int i=0; i<WAVE_TABLE_SIZE/rows; ++i) {
#ifdef PARTICLE
        Log.trace("%-5i %-5i %-5i %-5i %-5i %-5i %-5i %-5i %-5i %-5i %-5i %-5i %-5i %-5i %-5i %-5i",
            pulseWave[rows*i],
            pulseWave[rows*i+1],
            pulseWave[rows*i+2],
            pulseWave[rows*i+3],
            pulseWave[rows*i+4],
            pulseWave[rows*i+5],
            pulseWave[rows*i+6],
            pulseWave[rows*i+7],
            pulseWave[rows*i+8],
            pulseWave[rows*i+9],
            pulseWave[rows*i+10],
            pulseWave[rows*i+11],
            pulseWave[rows*i+12],
            pulseWave[rows*i+13],
            pulseWave[rows*i+14],
            pulseWave[rows*i+15]
        );
#endif
    }
}

void Oscillator::debug() {
#ifdef PARTICLE
    Log.trace("Clock: %d Sample: %d Freq: %f", _clock, getSample(), _frequency);
#endif
}