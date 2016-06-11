#include "synth.h"

Synth::Synth() {
	/*__timer = IntervalTimer();*/
}

Synth::~Synth() {
}

void Synth::begin() {
	// ~20kHz sampling
	/*__timer.begin(renderSample, 50, uSec);*/
}

void Synth::renderSample(void) {
	// Render each voice
	// Mix voices
	// Output to channels
}
