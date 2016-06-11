#ifndef FASTSID_SYNTH_ENGINE_H_
#define FASTSID_SYNTH_ENGINE_H_

#include "synth_engine.h"

#pragma once
/**
 * Synth engine using FastSID from VICE emulator
 */
class FastsidSynthEngine : SynthEngine {
	public:
		FastsidSynthEngine();
		virtual ~FastsidSynthEngine();

		void setAdsr(int attack, int decay, int sustain, int release);
};

#endif /* FASTSID_SYNTH_ENGINE_H_ */
