#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#pragma once

#if defined(PARTICLE)
#include "Particle.h"
#endif

#include <limits>
#include "types.h"
#include "../vendor/frannor.h"

class Oscillator {
    public:
        Oscillator();

        void setWaveform(Waveform waveform);
        void setFrequency(float frequency);
        void setPulseWidth(uint16_t pulseWidth);
        int16_t getSample();
        void clock();
        void debug();
    private:
        uint64_t _clock = 0;
        Waveform _waveform;
        float _frequency = 0;
        uint16_t _pulseWidth = (1 << 8) - 1;
        int16_t triangleWave[WAVE_TABLE_SIZE] = {0};
        int16_t sawtoothWave[WAVE_TABLE_SIZE] = {0};
        int16_t pulseWave[WAVE_TABLE_SIZE] = {0};

        void generateTriangleWave();
        void generateSawtoothWave();
        void generatePulseWave();
};

#endif //OSCILLATOR_H
