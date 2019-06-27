#if defined(PARTICLE)
#include "Particle.h"
SYSTEM_MODE(MANUAL);
SerialLogHandler dbg(LOG_LEVEL_NONE, { {"app", LOG_LEVEL_ALL} });
#else
#include <stdio.h>
#include <string.h>
#define delay(x) SDL_Delay(x)
#endif

#include "synth/synth.h"

void setup() {
#if defined(PARTICLE)
    waitUntil(Serial.isConnected);
#endif
    // Synth::instance()->voices[0].setWaveform(WF_PULSE);
    // Synth::instance()->voices[0].setFrequency(C4_HZ);
    Synth::instance()->voices[1].setWaveform(WF_TRIANGLE);
    Synth::instance()->voices[1].setFrequency(C4_HZ);
    Synth::instance()->begin();
}

#define SCALE
// #define PWM
// void loop() {}

#ifdef PWM
void loop() {
    Synth::instance()->voices[0].setWaveform(WF_PULSE);
    Synth::instance()->voices[0].setFrequency(C4_HZ);
    for (int16_t i = 0; i < (1 << 8); i+=8) {
        // Log.trace("Fill %i%% %i", float(i / (1 << 8) * 100), i);
        printf("Fill %f%% %i", float(i / (1 << 8) * 100), i);
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

#ifndef PARTICLE
int main(int argc, char **argv) {
    printf("ps-01\n");
    
    setup();

    while (1) {
        loop();
    }
}
#endif