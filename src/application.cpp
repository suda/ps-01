#if defined(PARTICLE)
#include "Particle.h"
SYSTEM_MODE(MANUAL);
#endif

#include "synth/synth.h"

void setup() {
	Synth::instance()->begin();
}

void loop() {}
