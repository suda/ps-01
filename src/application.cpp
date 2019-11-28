// #ifndef PARTICLE
// #define PARTICLE
// #endif
#include "util/types.h"
#if defined(PARTICLE)
#include "Particle.h"
#include "PCF8574.h"
SYSTEM_MODE(MANUAL);
SerialLogHandler dbg(LOG_LEVEL_NONE, { {"app", LOG_LEVEL_ALL} });

// Encoders
void encoderInterrupt();
PCF8574 encoders(0x20, ENCODER_INT_PIN, encoderInterrupt);
uint16_t state[4] = {0, 0, 0, 0};
int32_t lastPosition[4] = {0, 0, 0, 0};
bool encoderUpdated = false;

// Buttons
void buttonInterrupt();
PCF8574 buttons(0x21, BUTTON_INT_PIN, buttonInterrupt);
bool buttonUpdated = false;
#endif

// Encoder position
int32_t position[4] = {200, 200, 1 << 6, 500};

#include "synth/synth.h"
#include "ui/dispatcher.h"
#include "ui/keypad.h"
Dispatcher dispatcher = Dispatcher();
Keypad keypad = Keypad();

#if defined(PARTICLE)
void setupPCF(PCF8574 *pcf) {
    pcf->pinMode(P0, INPUT);
    pcf->pinMode(P1, INPUT);
    pcf->pinMode(P2, INPUT);
    pcf->pinMode(P3, INPUT);
    pcf->pinMode(P4, INPUT);
    pcf->pinMode(P5, INPUT);
    pcf->pinMode(P6, INPUT);
    pcf->pinMode(P7, INPUT);
    pcf->begin();
}

void encoderInterrupt() {
    encoderUpdated = true;
}

void buttonInterrupt() {
    buttonUpdated = true;
}

void calculateKnobPosition(uint8_t knob, uint8_t pinA, uint8_t pinB, uint8_t step=1) {
    uint8_t newState = state[knob] & 3;
    lastPosition[knob] = position[knob];
    if (pinA)
        newState |= 4;
    if (pinB)
        newState |= 8;
    state[knob] = (newState >> 2);
    switch (newState)
    {
        case 1:
        case 7:
        case 8:
        case 14:
            position[knob] -= step;
            return;
        case 2:
        case 4:
        case 11:
        case 13:
            position[knob] += step;
            return;
        case 3:
        case 12:
            position[knob] -= step * 2;
            return;
        case 6:
        case 9:
            position[knob] += step * 2;
            return;
    }
}
#endif

void setup() {
#if defined(PARTICLE)
    // waitUntil(Serial.isConnected);
    // delay(1000);
    Serial.println("ps-01");

    setupPCF(&encoders);
    setupPCF(&buttons);

    // drawKnobPositions(position[0], position[1], position[2], position[3]);
#endif
    keypad.begin(dispatcher);
    dispatcher.begin();
    Synth::instance()->begin();
}

// #define CYCLE
// #define PWM
// #define TRELLIS

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

#ifdef TRELLIS
float scale[] = { C4_HZ, C4S_HZ, D4_HZ, D4S_HZ, E4_HZ, F4_HZ, F4S_HZ, G4_HZ, G4S_HZ, A4_HZ, A4S_HZ, B4_HZ };

void loop() {
#if defined(PARTICLE)
    // delay(30);
    keypad.loop();
    
    if (encoderUpdated) {
        PCF8574::DigitalInput input = encoders.digitalReadAll();

        calculateKnobPosition(0, input.p0, input.p1, 16);
        calculateKnobPosition(1, input.p2, input.p3, 8);
        calculateKnobPosition(2, input.p4, input.p5, 4);
        calculateKnobPosition(3, input.p6, input.p7, 8);

        // Bound to min/max
        position[0] = max(min(position[0], 2 << 16), 0);
        position[1] = max(min(position[1], 2 << 16), 0);
        position[2] = max(min(position[2], 2 << 8), 0);
        position[3] = max(min(position[3], 2 << 16), 0);

        Serial.printf(
            "Attack:%4d | Decay:%4d | Sustain:%4d | Release:%4d\r",
            position[0],
            position[1],
            position[2],
            position[3]
        );
        
        Synth::instance()->voices[0].setADSR(position[0], position[1], position[2], position[3]);
        // drawKnobPositions(position[0], position[1], position[2], position[3]);
        encoderUpdated = false;
    }

    // The encoder flag is still set. Try pulling again
    if (digitalRead(ENCODER_INT_PIN) == LOW) {
        encoderUpdated = true;
    }

    if (buttonUpdated) {
        PCF8574::DigitalInput input = buttons.digitalReadAll();
        Serial.printf("Buttons: %d %d %d %d %d %d %d %d\r", 
            input.p0, input.p1, input.p2, input.p3,
            input.p4, input.p5, input.p6, input.p7);
        buttonUpdated = false;
    }

    // The button flag is still set. Try pulling again
    if (digitalRead(BUTTON_INT_PIN) == LOW) {
        buttonUpdated = true;
    }
#endif
}
#endif

void loop() {
    MK_ARGS(args, (int16_t)millis(), 0, 0, 0)
    dispatcher.dispatchAction(ACTION_TICK, args);
}

#ifndef PARTICLE
int main(int argc, char **argv) {
    printf("ps-01\n");
    setup();

    bool keep_window_open = true;
    while (keep_window_open) {
        SDL_Event e;
        while (SDL_PollEvent(&e) > 0) {
            switch(e.type) {
                case SDL_QUIT:
                    keep_window_open = false;
                    break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    keypad.handleKey(e);
                    break;
            }
        }
        loop();
        SDL_Delay(10);
    }
    dispatcher.end();
	SDL_Quit();
}
#endif