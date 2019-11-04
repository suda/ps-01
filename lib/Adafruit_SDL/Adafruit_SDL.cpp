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
    window = SDL_CreateWindow("ps-01", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SDL_WIDTH * SCALE, SDL_HEIGHT * SCALE, 0);
    if (!window) {
        std::cout << "Failed to create window\n";
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (!renderer) {
        std::cout << "Failed to create renderer\n";
        return;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SDL_WIDTH * SCALE, SDL_HEIGHT * SCALE);
    if (!texture) {
        std::cout << "Failed to create texture\n";
        return;
    }

    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderClear(renderer);
}

void Adafruit_SDL::update() {
    // SDL renderer doesn't guarantee its contents after being presented,
    // this is why we're rendering to a texture and then showing it instead
    // Thanks to Will Usher: https://gist.github.com/Twinklebear/8265888 
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);
	SDL_RenderCopyEx(renderer, texture, NULL, NULL, 0, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, texture);
}

void Adafruit_SDL::end() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

Uint8* rgb565to888(uint16_t color) {
    Uint8 *rgb = new Uint8[3];
    rgb[0] = (color & 0xF800) >> 8;
    rgb[1] = (color & 0x07E0) >> 3;
    rgb[2] = (color & 0x1F) << 3;

    return rgb;
}

void Adafruit_SDL::drawPixel(int16_t x, int16_t y, uint16_t color) {
    Uint8 *rgb = rgb565to888(color);
    SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
    SDL_RenderDrawPoint(renderer, x * SCALE, y * SCALE);
    SDL_RenderDrawPoint(renderer, x * SCALE + 1, y * SCALE);
    SDL_RenderDrawPoint(renderer, x * SCALE, y * SCALE + 1);
    SDL_RenderDrawPoint(renderer, x * SCALE + 1, y * SCALE + 1);
    free(rgb);
}
void Adafruit_SDL::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    Uint8 *rgb = rgb565to888(color);
    SDL_Rect rect;
    rect.x = x * SCALE;
    rect.y = y * SCALE;
    rect.w = w * SCALE;
    rect.h = h * SCALE;
    
    SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
    SDL_RenderFillRect(renderer, &rect);
    free(rgb);
}
void Adafruit_SDL::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    Uint8 *rgb = rgb565to888(color);
    SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
    SDL_RenderDrawLine(renderer, x * SCALE, y * SCALE, (x + w - 1) * SCALE, y * SCALE);
    SDL_RenderDrawLine(renderer, x * SCALE, y * SCALE + 1, (x + w - 1) * SCALE, y * SCALE + 1);
    free(rgb);
}
void Adafruit_SDL::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    Uint8 *rgb = rgb565to888(color);
    SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
    SDL_RenderDrawLine(renderer, x * SCALE, y * SCALE, x * SCALE, (y + h - 1) * SCALE);
    SDL_RenderDrawLine(renderer, x * SCALE + 1, y * SCALE, x * SCALE + 1, (y + h - 1) * SCALE);
    free(rgb);
}
#endif