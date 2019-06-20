#if defined(PARTICLE)
#include "Particle.h"
SYSTEM_MODE(MANUAL);
#endif

#include "synth/synth.h"

SerialLogHandler dbg(LOG_LEVEL_NONE, { {"app", LOG_LEVEL_ALL} });

void setup() {
	waitUntil(Serial.isConnected);
	Synth::instance()->begin();
}

#define SCALE
#ifndef SCALE
void loop() {
	
}
#else
#define C4_HZ 261.63
#define D4_HZ 293.66
#define E4_HZ 329.63
#define F4_HZ 349.23
#define G4_HZ 392.00
#define A4_HZ 440.00
#define B4_HZ 493.88
#define C5_HZ 523.25
float scale[] = { C4_HZ, D4_HZ, E4_HZ, F4_HZ, G4_HZ, A4_HZ, B4_HZ, C5_HZ, B4_HZ, A4_HZ, G4_HZ, F4_HZ, E4_HZ, D4_HZ };

void loop() {
	Synth::instance()->voices[0].setWaveform(WF_SAWTOOTH);
	for (int i=0; i<sizeof(scale)/sizeof(float); ++i) {
		Synth::instance()->voices[0].setFrequency(scale[i]);
		delay(1000);
	}
	Synth::instance()->voices[0].setWaveform(WF_TRIANGLE);
	for (int i=0; i<sizeof(scale)/sizeof(float); ++i) {
		Synth::instance()->voices[0].setFrequency(scale[i]);
		delay(1000);
	}
}
#endif