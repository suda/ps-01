#if !defined(PARTICLE)
#include "Adafruit_SDL.h"

#define SDL_WIDTH 320
#define SDL_HEIGHT 240

Adafruit_SDL::Adafruit_SDL() :
    Adafruit_GFX(SDL_WIDTH, SDL_HEIGHT) {
}

void Adafruit_SDL::begin() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize the SDL2 library\n";
        return;
    }

    window = SDL_CreateWindow("ps-01",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            680, 480,
                            0);

    if (!window) {
        std::cout << "Failed to create window\n";
        return;
    }

    screenSurface = SDL_GetWindowSurface(window);

    if (!screenSurface) {
        std::cout << "Failed to get the surface from the window\n";
        return;
    }

    SDL_UpdateWindowSurface(window);
}

void Adafruit_SDL::update() {
    SDL_UpdateWindowSurface(window);
}

void Adafruit_SDL::end() {
    SDL_DestroyWindow(window);
}

void Adafruit_SDL::drawPixel(int16_t x, int16_t y, uint16_t color) {
    // SDL_RenderDrawPoint(renderer, 400, 300); //Renders on middle of screen.
    // SDL_RenderPresent(renderer);
}
void Adafruit_SDL::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {}
void Adafruit_SDL::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {}
void Adafruit_SDL::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {}
#endif