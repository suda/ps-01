#include "oscillator.h"

Oscillator::Oscillator() {
    generateTriangleWave();
    generateSawtoothWave();
}

int16_t Oscillator::getSample() {
    float delta = (_frequency * WAVE_TABLE_SIZE) / float(SAMPLERATE_HZ);
    uint16_t pos = uint16_t(_clock * delta) % WAVE_TABLE_SIZE;
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
            return (int16_t)(AMPLITUDE * ((frannor() + 1.0) / 2.0));
            break;

        default:
            return 0;
            break;
    }
}

void Oscillator::clock() { _clock++; }

void Oscillator::setWaveform(Waveform waveform) { _waveform = waveform; }

void Oscillator::setFrequency(float frequency) { _frequency = frequency; }

void Oscillator::setPulseWidth(uint16_t pulseWidth) {
    _pulseWidth = pulseWidth;
    generatePulseWave();
}

void Oscillator::generateTriangleWave() {
    float delta = float(AMPLITUDE) / float(WAVE_TABLE_SIZE);
    for (int i = 0; i < WAVE_TABLE_SIZE / 2; ++i) {
        triangleWave[i] = -(AMPLITUDE / 2) + delta * (i * 2);
    }
    for (int i = 0; i < WAVE_TABLE_SIZE / 2; ++i) {
        triangleWave[(WAVE_TABLE_SIZE / 2) + i] =
            (AMPLITUDE / 2) - delta * (i * 2);
    }
}

void Oscillator::generateSawtoothWave() {
    float delta = float(AMPLITUDE) / float(WAVE_TABLE_SIZE);
    for (int i = 0; i < WAVE_TABLE_SIZE; ++i) {
        sawtoothWave[i] = -(AMPLITUDE / 2) + delta * i;
    }
}

void Oscillator::generatePulseWave() {
    for (int i = 0; i < WAVE_TABLE_SIZE; ++i) {
        pulseWave[i] = float(_pulseWidth) / float(WAVE_TABLE_SIZE) / 2 > i
                           ? AMPLITUDE / 2
                           : -(AMPLITUDE / 2);
    }
}

void Oscillator::debug() {
#ifdef PARTICLE
    Log.trace("Clock: %d Sample: %d Freq: %f", _clock, getSample(), _frequency);
#endif
}