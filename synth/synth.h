#ifndef SYNTH_H_
#define SYNTH_H_

#include "lib/SparkIntervalTimer/SparkIntervalTimer.h"
#include "fastsid_synth_engine.h"

#define CHANNEL_LEFT DAC1
#define CHANNEL_RIGHT DAC2

#pragma once
class Synth {
	IntervalTimer __timer;

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
