#ifndef VOICE_H_
#define VOICE_H_

#pragma once

#include "oscillator.h"
#include "types.h"

/**
 * A voice is a single sound generator. This class contains all its parameters
 * which should be used by synth engine when rendering samples.
 */
class Voice {
    public:
        Voice();

        void setWaveform(Waveform waveform);
        void setFrequency(float frequency);
        void setPulseWidth(uint16_t pulseWidth);
        void setADSR(uint16_t attack, uint16_t decay, uint16_t sustain, uint16_t release);
        // Set to true for Attack/Decay/Sustain cycle and false for Release cycle
        void setGate(bool gate);
        void setChannel(Channel channel);
        int16_t getSample();
        void clock();
        void debug();
    private:
        Oscillator oscillator;
        uint64_t _clock = 0;
};

#endif /* VOICE_H_ */
