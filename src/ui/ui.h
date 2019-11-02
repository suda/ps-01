#pragma once

#if defined(PARTICLE)
  #include "Adafruit_GFX.h"
  #include "Adafruit_ILI9341.h"
#else
  #include <stdio.h>
  #include <string.h>
  #include "../../lib/Adafruit_SDL/Adafruit_SDL.h"
#endif
// Include all pages
#include "pages/scale_test_page.h"

class UI {
    public:
        UI();
        void begin();
        void update();
        void end();

    private:
        void initPages();
        void clearScreen();
        void drawButton();
        void drawKnobPositions(uint16_t attack, uint16_t decay, uint8_t sustain, uint16_t release);
#if defined(PARTICLE)
        Adafruit_ILI9341 tft;
#else
        Adafruit_SDL tft;
#endif
        Page currentPage;

        ScaleTestPage scaleTestPage;
};