#if defined(PARTICLE)
#include "Particle.h"
SYSTEM_MODE(MANUAL);
#endif

#include "synth/synth.h"

SerialLogHandler dbg(LOG_LEVEL_NONE, { {"app", LOG_LEVEL_ALL} });

void setup() {
    waitUntil(Serial.isConnected);
    Synth::instance()->voices[0].setWaveform(WF_TRIANGLE);
    Synth::instance()->begin();
}

#define C4_HZ 261.63
#define D4_HZ 293.66
#define E4_HZ 329.63
#define F4_HZ 349.23
#define G4_HZ 392.00
#define A4_HZ 440.00
#define B4_HZ 493.88
#define C5_HZ 523.25

// #define SCALE
#define PWM

#ifdef PWM
void loop() {
    Synth::instance()->voices[0].setWaveform(WF_PULSE);
    Synth::instance()->voices[0].setFrequency(C4_HZ);
    for (int16_t i = 0; i < (1 << 8); i+=8) {
        Log.trace("Fill %i%% %i", float(i / (1 << 8) * 100), i);
        Synth::instance()->voices[0].setPulseWidth(i);
        delay(1000);
    }
}
#endif

#ifdef NOISE
int del = 500;
void loop() {
    Synth::instance()->voices[0].setWaveform(WF_NOISE);
    Synth::instance()->voices[0].setFrequency(C4_HZ);
    delay(del);
    Synth::instance()->voices[0].setFrequency(E4_HZ);
    delay(del);
    Synth::instance()->voices[0].setFrequency(G4_HZ);
    delay(del);
}
#endif

#ifdef SCALE
float scale[] = { C4_HZ, D4_HZ, E4_HZ, F4_HZ, G4_HZ, A4_HZ, B4_HZ, C5_HZ, B4_HZ, A4_HZ, G4_HZ, F4_HZ, E4_HZ, D4_HZ };

void loop() {
    Synth::instance()->voices[0].setWaveform(WF_SAWTOOTH);
    for (int i=0; i<sizeof(scale)/sizeof(float); ++i) {
        Synth::instance()->voices[0].setFrequency(scale[i]);
        delay(500);
    }
    Synth::instance()->voices[0].setWaveform(WF_TRIANGLE);
    for (int i=0; i<sizeof(scale)/sizeof(float); ++i) {
        Synth::instance()->voices[0].setFrequency(scale[i]);
        delay(500);
    }
}
#endif