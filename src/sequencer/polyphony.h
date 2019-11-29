#pragma once

#include "../util/types.h"
#include "../synth/synth.h"

class Polyphony {
    public:
        Polyphony();
        static Polyphony *instance() {
            static Polyphony p;
            return &p;
        }

        bool startFrequency(float frequency);
        bool stopFrequency(float frequency);
    private:
        float _voices[VOICES_COUNT];
        int8_t _getFrequencyIndex(float frequency);
        int8_t _getAvailableIndex();
};