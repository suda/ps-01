#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#pragma once

#if defined(PARTICLE)
#include "Particle.h"
#endif

#include "types.h"

#define SAMPLERATE_HZ   44100
// #define AMPLITUDE       ((1<<15)-1)
#define AMPLITUDE       ((1<<12)-1)
#define WAVE_TABLE_SIZE 256

class Oscillator {
    public:
        Oscillator();

        void setWaveform(Waveform waveform);
        void setFrequency(float frequency);
        void setPulseWidth(int8_t pulseWidth);
        int16_t getSample();
        void clock();
        void debug();
    private:
        uint64_t _clock = 0;
        Waveform _waveform;
        float _frequency = 0;
        int16_t triangleWave[WAVE_TABLE_SIZE] = {0};
        int16_t sawtoothWave[WAVE_TABLE_SIZE] = {0};

        void generateTriangleWave();
        void generateSawtoothWave();
};

#endif //OSCILLATOR_H
