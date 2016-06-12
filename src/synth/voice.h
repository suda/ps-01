#ifndef VOICE_H_
#define VOICE_H_

#pragma once

typedef enum {
	ATTACK  = 0,
	DECAY   = 1,
	SUSTAIN = 2,
	RELEASE = 3,
	IDLE    = 4
} AdsrState;

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
        void setFrequency(int frequency);
        void setPulseWidth(int pulseWidth);
        void setAdsr(int attack, int decay, int sustain, int release);
        // Set to true for Attack/Decay/Sustain cycle and false for Release cycle
        void setGate(bool gate);
        void setChannel(Channel channel);
};

#endif /* VOICE_H_ */
