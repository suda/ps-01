#ifndef VOICE_H_
#define VOICE_H_

#pragma once

#include "oscillator.h"

typedef enum {
	ATTACK  = 0,
	DECAY   = 1,
	SUSTAIN = 2,
	RELEASE = 3,
	IDLE    = 4
} ADSRState;

typedef enum {
	TEST     = 0,
	PULSE    = 1,
	SAWTOOTH = 2,
	TRIANGLE = 3,
	NOISE    = 4,
	NO_WAVE  = 5
} Waveform;

typedef enum {
    BOTH  = 0,
    LEFT  = 1,
    RIGHT = 2
} Channel;

/**
 * A voice is a single sound generator. This class contains all its parameters
 * which should be used by synth engine when rendering samples.
 */
class Voice {
	public:
		Voice();
		virtual ~Voice();

		void setWaveform(Waveform waveform);
        void setFrequency(uint16_t frequency);
        void setPulseWidth(uint16_t pulseWidth);
        void setADSR(uint16_t attack, uint16_t decay, uint16_t sustain, uint16_t release);
        // Set to true for Attack/Decay/Sustain cycle and false for Release cycle
        void setGate(bool gate);
        void setChannel(Channel channel);
	private:
		Oscillator oscillator;
};

#endif /* VOICE_H_ */
