#include "synth.h"

Synth::Synth() {
#if defined(PARTICLE)
    __timer = IntervalTimer();
    __output = DacSoundOutput();
#else
    // TODO: Boost timer
    __output = FileSoundOutput();
#endif
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
