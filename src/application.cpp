// #ifndef PARTICLE
// #define PARTICLE
// #endif
#if defined(PARTICLE)
#include "Particle.h"
#include "Adafruit_Trellis.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "PCF8574.h"
#include "synth/types.h"
SYSTEM_MODE(MANUAL);
SerialLogHandler dbg(LOG_LEVEL_NONE, { {"app", LOG_LEVEL_ALL} });

// Trellis pad
Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);
bool keypadUpdated = false;
uint16_t keypadState = 0;
void keypadInterrupt();
Timer keyUpTimer(50, keypadInterrupt, true);

// Encoders
void encoderInterrupt();
PCF8574 encoders(0x20, ENCODER_INT_PIN, encoderInterrupt);
uint16_t state[4] = {0, 0, 0, 0};
int32_t lastPosition[4] = {0, 0, 0, 0};
bool encoderUpdated = false;

// TFT
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
#else
#include <stdio.h>
#include <string.h>
#define delay(x) SDL_Delay(x)
#endif

// Encoder position
int32_t position[4] = {200, 200, 1 << 6, 500};

#include "synth/synth.h"

#if defined(PARTICLE)
void keypadInterrupt() {
    keypadUpdated = true;
}

void setupEncoders() {
    encoders.pinMode(P0, INPUT);
    encoders.pinMode(P1, INPUT);
    encoders.pinMode(P2, INPUT);
    encoders.pinMode(P3, INPUT);
    encoders.pinMode(P4, INPUT);
    encoders.pinMode(P5, INPUT);
    encoders.pinMode(P6, INPUT);
    encoders.pinMode(P7, INPUT);
    encoders.begin();
}

void encoderInterrupt() {
    encoderUpdated = true;
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

// 5 - 6 - 5
#define COLOR_BG               0x00E4  ///< 155, 188,  16
#define COLOR_BLUE             0x45FF
#define COLOR_BLUE_SHADOW      0x2397
#define COLOR_DIALOG_BG        0xE7BE
#define COLOR_IN_DIALOG_SHADOW 0x9699

void clearScreen() {
    tft.setRotation(3);
    tft.fillScreen(COLOR_BG);
}

void drawKnobPositions(uint16_t attack, uint16_t decay, uint8_t sustain, uint16_t release) {
    uint8_t corner = 4;
    uint8_t width = 160;
    uint8_t height = 48;
    uint8_t x = 80;
    uint8_t y = 70;

    // Dialog
    tft.fillRect(50, 30, 220, 180, COLOR_DIALOG_BG);

    // Top
    tft.fillRect(50+corner, 30-corner, 220-(corner*2), corner, COLOR_DIALOG_BG);
    tft.fillRect(50+(corner*2), 30-(corner*2), 220-(corner*4), corner, COLOR_DIALOG_BG);

    // Bottom
    tft.fillRect(50+corner, 210, 220-(corner*2), corner, COLOR_DIALOG_BG);
    tft.fillRect(50, 210, corner, corner, COLOR_IN_DIALOG_SHADOW);
    tft.fillRect(50+220-corner, 210, corner, corner, COLOR_IN_DIALOG_SHADOW);
    tft.fillRect(50+(corner*2), 210+corner, 220-(corner*4), corner, COLOR_DIALOG_BG);
    tft.fillRect(50+corner, 210+corner, corner, corner, COLOR_IN_DIALOG_SHADOW);
    tft.fillRect(50+220-(corner*2), 210+corner, corner, corner, COLOR_IN_DIALOG_SHADOW);
    tft.fillRect(50+(corner*2), 210+(corner*2), 220-(corner*4), corner, COLOR_IN_DIALOG_SHADOW);

    // Button
    tft.fillRect(x, y, width, height, COLOR_BLUE);
    tft.fillRect(x, y+height, width, corner, COLOR_BLUE_SHADOW);
    tft.fillRect(x, y+height+corner, width, corner, COLOR_IN_DIALOG_SHADOW);

    tft.fillRect(x-corner, y+corner, corner, height-corner, COLOR_BLUE);
    tft.fillRect(x-corner, y+height-corner, corner, corner, COLOR_BLUE_SHADOW);
    tft.fillRect(x-corner, y+height, corner, corner, COLOR_IN_DIALOG_SHADOW);

    tft.fillRect(x+width, y+corner, corner, height-corner, COLOR_BLUE);
    tft.fillRect(x+width, y+height-corner, corner, corner, COLOR_BLUE_SHADOW);
    tft.fillRect(x+width, y+height, corner, corner, COLOR_IN_DIALOG_SHADOW);
    
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(4);
    tft.setCursor(x+(width/2) - (2*24)-12, y+8+4);
    tft.print("PS-01");

    return;
    // 320 / 4 = 80
    tft.fillCircle(40, 120, 20, ILI9341_RED);

    tft.fillCircle(80+40, 120, 20, ILI9341_GREEN);

    tft.fillCircle((80*2)+40, 120, 20, ILI9341_BLUE);

    tft.fillCircle((80*3)+40, 120, 20, ILI9341_WHITE);
}
#endif

void setup() {
#if defined(PARTICLE)
    // waitUntil(Serial.isConnected);

    Wire.setSpeed(CLOCK_SPEED_400KHZ);
    pinMode(KEYPAD_INT_PIN, INPUT_PULLUP);
    attachInterrupt(KEYPAD_INT_PIN, keypadInterrupt, CHANGE);
    trellis.begin(0x70);

    setupEncoders();

    tft.begin();
    clearScreen();
    drawKnobPositions(position[0], position[1], position[2], position[3]);
#endif
    Synth::instance()->voices[0].setWaveform(WF_TRIANGLE);
    Synth::instance()->voices[0].setFrequency(C4_HZ);
    Synth::instance()->voices[0].setADSR(position[0], position[1], position[2], position[3]);
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
#if defined(PARTICLE)
    // delay(30);
    if (keypadUpdated) {
        if (trellis.readSwitches()) {
            bool keypadChanged = false;
            bool anyKeyPressed = false;
            for (uint8_t i=0; i<16; i++) {
                bool state = trellis.isKeyPressed(i);
                anyKeyPressed |= state;
                if (state != BIT_CHECK(keypadState, i)) {
                    // State changed
                    keypadChanged = true;

                    if (state) {
                        trellis.setLED(i);
                        BIT_SET(keypadState, i);
                        Synth::instance()->voices[0].setFrequency(scale[i]);
                        Synth::instance()->voices[0].setGate(true);
                    } else {
                        trellis.clrLED(i);
                        BIT_CLEAR(keypadState, i);
                        Synth::instance()->voices[0].setGate(false);
                    }
                }
            }
            
            if (keypadChanged) {
                trellis.writeDisplay();
            }

            // This is silly but necessary. HT16K33 doesn't trigger interrup
            // on key up so we need to check manually with a timer
            if (anyKeyPressed) {
                keyUpTimer.reset();
            }
        } else {
            keyUpTimer.reset();
        }
        keypadUpdated = false;
    }
    
    if (encoderUpdated) {
        PCF8574::DigitalInput input = encoders.digitalReadAll();

        calculateKnobPosition(0, input.p0, input.p1, 16);
        calculateKnobPosition(1, input.p2, input.p3, 8);
        calculateKnobPosition(2, input.p4, input.p5, 4);
        calculateKnobPosition(3, input.p6, input.p7, 8);

        Serial.printf(
            "Attack:%4d | Decay:%4d | Sustain:%4d | Release:%4d\r",
            position[0],
            position[1],
            position[2],
            position[3]
        );
        position[0] = max(min(position[0], 2 << 16), 0);
        position[1] = max(min(position[1], 2 << 16), 0);
        position[2] = max(min(position[2], 2 << 8), 0);
        position[3] = max(min(position[3], 2 << 16), 0);
        Synth::instance()->voices[0].setADSR(position[0], position[1], position[2], position[3]);
        drawKnobPositions(position[0], position[1], position[2], position[3]);
        encoderUpdated = false;
    }
#endif
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