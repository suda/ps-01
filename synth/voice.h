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

/**
 * A voice is a single sound generator. This class contains all its parameters
 * which should be used by synth engine when rendering samples.
 */
class Voice {
	public:
		Voice();
		virtual ~Voice();

		void setAdsr(int attack, int decay, int sustain, int release);
		void setWaveform(Waveform waveform);
};

#endif /* VOICE_H_ */
