#ifndef SYNTH_ENGINE_H_
#define SYNTH_ENGINE_H_

#include <stdint.h>
#include "voice.h"

#pragma once
/**
 * Synth engine interface definition.
 */
class SynthEngine {
	public:
		virtual ~SynthEngine();

		virtual int16_t calculateSample(int i) = 0;
		virtual Voice getVoice(int voiceNumber) = 0;
};

#endif /* SYNTH_ENGINE_H_ */
