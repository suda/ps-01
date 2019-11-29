#pragma once

#include "../util/types.h"

class ADSR {
    public:
        ADSR();

        void setAttack(uint16_t attack);
        void setDecay(uint16_t decay);
        void setSustain(uint8_t sustain);
        void setRelease(uint16_t release);
        void setGate(bool gate);
        void clock();
        void debug();
        // Apply ADSR and return the sample
        int16_t apply(int16_t sample);
    private:
        uint16_t _attack;
        uint16_t _decay;
        uint8_t _sustain;
        uint16_t _release;
        uint64_t _clock = 0;
        float _oneMSf;
        float _decayf;
        float _decayOneMSf;
        float _sustainf;
        float _sustainInvf;
        float _releasef;
        float _releaseOneMSf;
        bool _gate = false;
        ADSRState _state = ADSR_IDLE;
};