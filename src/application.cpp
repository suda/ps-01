#if defined(PARTICLE)
#include "Particle.h"
#include "Adafruit_Trellis.h"
SYSTEM_MODE(MANUAL);
SerialLogHandler dbg(LOG_LEVEL_NONE, { {"app", LOG_LEVEL_ALL} });

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);
#else
#include <stdio.h>
#include <string.h>
#define delay(x) SDL_Delay(x)
#endif

#include "synth/synth.h"

void setup() {
#if defined(PARTICLE)
    waitUntil(Serial.isConnected);

    Wire.setSpeed(CLOCK_SPEED_400KHZ);
    trellis.begin(0x70);
#endif
    Synth::instance()->voices[0].setWaveform(WF_TRIANGLE);
    Synth::instance()->voices[0].setFrequency(C4_HZ);
    Synth::instance()->voices[0].setADSR(200, 200, 1 << 6, 500);
    // Synth::instance()->voices[1].setWaveform(WF_SAWTOOTH);
    // Synth::instance()->voices[1].setFrequency(C4_HZ);
    Synth::instance()->begin();
}

// #define CYCLE
// #define SCALE
// #define PWM
#define TRELLIS

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
// float scale[] = { C4_HZ, D4_HZ, E4_HZ, F4_HZ, G4_HZ, A4_HZ, B4_HZ, C5_HZ, B4_HZ, A4_HZ, G4_HZ, F4_HZ, E4_HZ, D4_HZ };
float scale[] = { C4_HZ, D4_HZ, E4_HZ, F4_HZ, G4_HZ, A4_HZ, B4_HZ, C5_HZ };

void loop() {
    Synth::instance()->voices[0].setWaveform(WF_TRIANGLE);
    for (int i=0; i<sizeof(scale)/sizeof(float); ++i) {
        trellis.setLED(i);
        trellis.writeDisplay();
        Synth::instance()->voices[0].setFrequency(scale[i]);
        Synth::instance()->voices[0].setGate(true);
        delay(600);
        Synth::instance()->voices[0].setGate(false);
        delay(1000);
        trellis.clrLED(i);
        trellis.writeDisplay();
    }
    // Synth::instance()->voices[0].setWaveform(WF_TRIANGLE);
    // for (int i=0; i<sizeof(scale)/sizeof(float); ++i) {
    //     Synth::instance()->voices[0].setFrequency(scale[i]);
    //     delay(500);
    // }
}
#endif

#ifdef TRELLIS
float scale[] = { C4_HZ, C4S_HZ, D4_HZ, D4S_HZ, E4_HZ, F4_HZ, F4S_HZ, G4_HZ, G4S_HZ, A4_HZ, A4S_HZ, B4_HZ };

void loop() {
    delay(30);
    if (trellis.readSwitches()) {
        bool keyChanged = false;
        for (int i=0; i<16; i++) {
            if (trellis.justPressed(i)) {
                trellis.setLED(i);
                keyChanged = true;
                Synth::instance()->voices[0].setFrequency(scale[i]);
                Synth::instance()->voices[0].setGate(true);
            } 
            if (trellis.justReleased(i)) {
                trellis.clrLED(i);
                keyChanged = true;
                Synth::instance()->voices[0].setGate(false);
            }
        }
        
        if (keyChanged) {
            trellis.writeDisplay();
        }
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