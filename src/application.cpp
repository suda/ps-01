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
    Synth::instance()->voices[0].setWaveform(WF_TRIANGLE);
    Synth::instance()->voices[0].setFrequency(C4_HZ);
    Synth::instance()->voices[0].setADSR(200, 200, 1 << 5, 500);
    // Synth::instance()->voices[1].setWaveform(WF_SAWTOOTH);
    // Synth::instance()->voices[1].setFrequency(C4_HZ);
    Synth::instance()->begin();
}

// #define CYCLE
#define SCALE
// #define PWM

#ifdef CYCLE
void loop() {
    delay(1000);
    Synth::instance()->voices[0].setWaveform(WF_NOISE);
    delay(1000);
    Synth::instance()->voices[0].setWaveform(WF_PULSE);
    delay(1000);
    Synth::instance()->voices[0].setWaveform(WF_SAWTOOTH);
    delay(1000);
    Synth::instance()->voices[0].setWaveform(WF_TRIANGLE);
}
#endif

#ifdef PWM
void loop() {
    Synth::instance()->voices[0].setWaveform(WF_PULSE);
    Synth::instance()->voices[0].setFrequency(C4_HZ);
    uint16_t maxPW = (1 << 16) / 1 - 1;
    uint16_t steps = 16;
    for (uint16_t i = 0; i < maxPW; i+=maxPW / steps) {
        Log.trace("Fill %.0f%% %i", float(i) / maxPW * 100, i);
        // printf("Fill %.0f%% %i\n", float(i) / maxPW * 100, i);
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
        Synth::instance()->voices[0].setGate(true);
        delay(600);
        Synth::instance()->voices[0].setGate(false);
        delay(1000);
    }
    // Synth::instance()->voices[0].setWaveform(WF_TRIANGLE);
    // for (int i=0; i<sizeof(scale)/sizeof(float); ++i) {
    //     Synth::instance()->voices[0].setFrequency(scale[i]);
    //     delay(500);
    // }
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