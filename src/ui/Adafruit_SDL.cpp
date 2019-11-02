#if !defined(PARTICLE)
#include "Adafruit_SDL.h"

#define SDL_WIDTH 320
#define SDL_HEIGHT 240
#define SCALE 2

Adafruit_SDL::Adafruit_SDL() :
    Adafruit_GFX(SDL_WIDTH, SDL_HEIGHT) {
}

void Adafruit_SDL::begin() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize the SDL2 library\n";
        return;
    }

    SDL_CreateWindowAndRenderer(SDL_WIDTH * SCALE, SDL_HEIGHT * SCALE, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "ps-01");
    if (!window) {
        std::cout << "Failed to create window\n";
        return;
    }
}

void Adafruit_SDL::update() {
    SDL_RenderPresent(renderer);
}

void Adafruit_SDL::end() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Adafruit_SDL::drawPixel(int16_t x, int16_t y, uint16_t color) {
    Uint8 r = (color & 0xF800) >> 8;
    Uint8 g = (color & 0x07E0) >> 3;
    Uint8 b = (color & 0x1F) << 3;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawPoint(renderer, x * SCALE, x * SCALE);
}
void Adafruit_SDL::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    Uint8 r = (color & 0xF800) >> 8;
    Uint8 g = (color & 0x07E0) >> 3;
    Uint8 b = (color & 0x1F) << 3;
    SDL_Rect rect;
    rect.x = x * SCALE;
    rect.y = y * SCALE;
    rect.w = w * SCALE;
    rect.h = h * SCALE;
    
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);

}
void Adafruit_SDL::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {}
void Adafruit_SDL::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {}
#endif