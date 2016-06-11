#ifndef SYNTH_H_
#define SYNTH_H_

#if defined(PARTICLE)
#include "SparkIntervalTimer.h"

#define CHANNEL_LEFT DAC1
#define CHANNEL_RIGHT DAC2
#endif

#include "fastsid_synth_engine.h"

#pragma once
class Synth {
#if defined(PARTICLE)
	IntervalTimer __timer;
#endif

	public:
		Synth();
		virtual ~Synth();

		void
			begin();

	private:
		void
			renderSample(void);
};

#endif /* SYNTH_H_ */
