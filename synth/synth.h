#ifndef SYNTH_H_
#define SYNTH_H_

#include <SparkIntervalTimer.h>

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
}

#endif /* SYNTH_H_ */
