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

// Buttons
void buttonInterrupt();
PCF8574 buttons(0x21, BUTTON_INT_PIN, buttonInterrupt);
bool buttonUpdated = false;

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

// 5 - 6 - 5
#define COLOR_BG               0x2A28
#define COLOR_BLUE             0x663F
#define COLOR_BLUE_SHADOW      0x3BF8
#define COLOR_GREEN            0x5F92
#define COLOR_GREEN_SHADOW     0x34EF
#define COLOR_PURPLE           0xCC9E
#define COLOR_PURPLE_SHADOW    0x82B7
#define COLOR_RED              0xF22B
#define COLOR_RED_SHADOW       0x984A
#define COLOR_DIALOG           0xEFDF
#define COLOR_DIALOG_SHADOW    0xA6BA

void clearScreen() {
    tft.setRotation(3);
    tft.fillScreen(COLOR_BG);
}

void drawButton() {
    uint8_t corner = 4;
    uint8_t width = 160;
    uint8_t height = 48;
    uint8_t x = 80;
    uint8_t y = 70;

    // Dialog
    tft.fillRect(50, 30, 220, 180, COLOR_DIALOG);

    // Top
    tft.fillRect(50+corner, 30-corner, 220-(corner*2), corner, COLOR_DIALOG);
    tft.fillRect(50+(corner*2), 30-(corner*2), 220-(corner*4), corner, COLOR_DIALOG);

    // Bottom
    tft.fillRect(50+corner, 210, 220-(corner*2), corner, COLOR_DIALOG);
    tft.fillRect(50, 210, corner, corner, COLOR_DIALOG_SHADOW);
    tft.fillRect(50+220-corner, 210, corner, corner, COLOR_DIALOG_SHADOW);
    tft.fillRect(50+(corner*2), 210+corner, 220-(corner*4), corner, COLOR_DIALOG);
    tft.fillRect(50+corner, 210+corner, corner, corner, COLOR_DIALOG_SHADOW);
    tft.fillRect(50+220-(corner*2), 210+corner, corner, corner, COLOR_DIALOG_SHADOW);
    tft.fillRect(50+(corner*2), 210+(corner*2), 220-(corner*4), corner, COLOR_DIALOG_SHADOW);

    // Button
    tft.fillRect(x, y, width, height, COLOR_BLUE);
    tft.fillRect(x, y+height, width, corner, COLOR_BLUE_SHADOW);
    tft.fillRect(x, y+height+corner, width, corner, COLOR_DIALOG_SHADOW);

    tft.fillRect(x-corner, y+corner, corner, height-corner, COLOR_BLUE);
    tft.fillRect(x-corner, y+height-corner, corner, corner, COLOR_BLUE_SHADOW);
    tft.fillRect(x-corner, y+height, corner, corner, COLOR_DIALOG_SHADOW);

    tft.fillRect(x+width, y+corner, corner, height-corner, COLOR_BLUE);
    tft.fillRect(x+width, y+height-corner, corner, corner, COLOR_BLUE_SHADOW);
    tft.fillRect(x+width, y+height, corner, corner, COLOR_DIALOG_SHADOW);
    
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(4);
    tft.setCursor(x+(width/2) - (2*24)-12, y+8+4);
    tft.print("PS-01");
}
void drawKnobPositions(uint16_t attack, uint16_t decay, uint8_t sustain, uint16_t release) {
    // 320 / 4 = 80
    uint8_t radius = 32;
    uint8_t y = 128;
    uint8_t offset = 4;
    uint8_t textY = y+radius+(offset*2);
    tft.fillRect(0, textY, 320, 16, COLOR_BG);
    tft.setTextSize(2);

    // tft.fillCircle(40+offset, y+offset, radius, COLOR_BLUE_SHADOW);
    // tft.fillCircle(40, y, radius, COLOR_BLUE);
    tft.setCursor(40-radius, textY);
    tft.setTextColor(COLOR_BLUE);
    tft.print(attack);

    // tft.fillCircle(80+40+offset, y+offset, radius, COLOR_GREEN_SHADOW);
    // tft.fillCircle(80+40, y, radius, COLOR_GREEN);
    tft.setCursor(80+40-radius, textY);
    tft.setTextColor(COLOR_GREEN);
    tft.print(decay);

    // tft.fillCircle((80*2)+40+offset, y+offset, radius, COLOR_PURPLE_SHADOW);
    // tft.fillCircle((80*2)+40, y, radius, COLOR_PURPLE);
    tft.setCursor((80*2)+40-radius, textY);
    tft.setTextColor(COLOR_PURPLE);
    tft.print(sustain);

    // tft.fillCircle((80*3)+40+offset, y+offset, radius, COLOR_RED_SHADOW);
    // tft.fillCircle((80*3)+40, y, radius, COLOR_RED);
    tft.setCursor((80*3)+40-radius, textY);
    tft.setTextColor(COLOR_RED);
    tft.print(release);
}
#endif

void setup() {
#if defined(PARTICLE)
    // waitUntil(Serial.isConnected);

    Wire.setSpeed(CLOCK_SPEED_400KHZ);
    pinMode(KEYPAD_INT_PIN, INPUT_PULLUP);
    attachInterrupt(KEYPAD_INT_PIN, keypadInterrupt, CHANGE);
    trellis.begin(0x70);

    setupPCF(&encoders);
    setupPCF(&buttons);

    tft.begin();
    clearScreen();
    // drawButton();
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

#ifndef PARTICLE
int main(int argc, char **argv) {
    printf("ps-01\n");
    
    setup();

    while (1) {
        loop();
    }
}
#endif