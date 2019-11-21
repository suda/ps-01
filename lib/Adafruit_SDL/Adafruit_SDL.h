#ifndef ADAFRUIT_SDL_H
#define ADAFRUIT_SDL_H

#if !defined(PARTICLE)
#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include "../Adafruit_GFX/src/Adafruit_GFX.h"

class Adafruit_SDL : public Adafruit_GFX {
    public:
        Adafruit_SDL();
        void begin();
        void update();
        void end();
        void drawPixel(int16_t x, int16_t y, uint16_t color);
        void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                      uint16_t color);
        void drawFastHLine(int16_t x, int16_t y, int16_t w,
                           uint16_t color);
        void drawFastVLine(int16_t x, int16_t y, int16_t h,
                           uint16_t color);
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *texture;
};
#endif

#endif // ADAFRUIT_SDL_H