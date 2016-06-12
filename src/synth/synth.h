#ifndef SYNTH_H_
#define SYNTH_H_

#if defined(PARTICLE)
#include "SparkIntervalTimer.h"
#include "dac_sound_output.h"
#else
#include <stdint.h>
#include "file_sound_output.h"
#endif

#include "voice.h"

#pragma once
class Synth {
#if defined(PARTICLE)
	IntervalTimer __timer;
    DacSoundOutput __output;
#else
    // TODO: Timer from Boost
	FileSoundOutput __output;
#endif

	public:
		Synth();
		virtual ~Synth();

		void
			begin();

		Voice getVoice(int voiceNumber);

	private:
		void
			renderSample(void);
};

#endif /* SYNTH_H_ */
