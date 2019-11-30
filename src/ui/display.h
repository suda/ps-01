#pragma once

#include "../../lib/Adafruit_GFX/src/Adafruit_GFX.h"
#include "../util/types.h"
#include "ui.h"
#if defined(PARTICLE)
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#else
#include "../../lib/Adafruit_SDL/Adafruit_SDL.h"
#endif

class Display {
   public:
    Display();
    void begin();
    void update();
    void end();
    void clearScreen();
    void drawDialog();
    void drawTab(uint16_t x, String label, uint16_t color, uint16_t shadowColor);
    void drawTabs(String labelA, String labelB, String labelC, String labelD);
    void drawButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
                    uint16_t color, uint16_t shadowColor);
    void drawKnobPositions(uint16_t attack, uint16_t decay, uint8_t sustain,
                           uint16_t release);
    void drawKeys(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t keyWidth, uint8_t keys);
    void drawKey(uint16_t x, uint16_t y, uint16_t height, uint8_t keyWidth, uint8_t key, uint16_t color);

#if defined(PARTICLE)
    Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
#else
    Adafruit_SDL tft;
#endif
};