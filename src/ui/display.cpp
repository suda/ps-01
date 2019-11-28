#include "display.h"

Display::Display() {}

void Display::begin() {
#if !defined(PARTICLE)
    tft = Adafruit_SDL();
#endif

    tft.begin();
    clearScreen();
#if !defined(PARTICLE)
    tft.update();
#endif
}

void Display::update() {
#if !defined(PARTICLE)
    tft.update();
#endif
}

void Display::end() {
#if !defined(PARTICLE)
    tft.end();
#endif
}

void Display::clearScreen() {
#if defined(PARTICLE)
    tft.setRotation(3);
#endif
    tft.fillScreen(COLOR_BG);
}

void Display::drawDialog() {
    uint16_t x = CORNER_SIZE*2;
    uint16_t y = CORNER_SIZE*4;
    uint16_t w = 320-(CORNER_SIZE*4);
    uint16_t h = 176;

    // Background
    tft.fillRect(x, y, w, h, COLOR_DIALOG);

    // Top
    tft.fillRect(x+CORNER_SIZE, y-CORNER_SIZE, w-(CORNER_SIZE*2), CORNER_SIZE, COLOR_DIALOG);
    tft.fillRect(x+(CORNER_SIZE*2), y-(CORNER_SIZE*2), w-(CORNER_SIZE*4), CORNER_SIZE, COLOR_DIALOG);

    // Bottom
    tft.fillRect(x+CORNER_SIZE, y+h, w-(CORNER_SIZE*2), CORNER_SIZE, COLOR_DIALOG);
    tft.fillRect(x, y+h, CORNER_SIZE, CORNER_SIZE, COLOR_DIALOG_SHADOW);
    tft.fillRect(x+w-CORNER_SIZE, y+h, CORNER_SIZE, CORNER_SIZE, COLOR_DIALOG_SHADOW);
    tft.fillRect(x+(CORNER_SIZE*2), y+h+CORNER_SIZE, w-(CORNER_SIZE*4), CORNER_SIZE, COLOR_DIALOG);
    tft.fillRect(x+CORNER_SIZE, y+h+CORNER_SIZE, CORNER_SIZE, CORNER_SIZE, COLOR_DIALOG_SHADOW);
    tft.fillRect(x+w-(CORNER_SIZE*2), y+h+CORNER_SIZE, CORNER_SIZE, CORNER_SIZE, COLOR_DIALOG_SHADOW);
    tft.fillRect(x+(CORNER_SIZE*2), y+h+(CORNER_SIZE*2), w-(CORNER_SIZE*4), CORNER_SIZE, COLOR_DIALOG_SHADOW);
}

void Display::drawTab(uint16_t x, uint16_t color, uint16_t shadowColor) {
    tft.fillRect(x, 214+(CORNER_SIZE*2), 72, 18, color);
    tft.fillRect(x+CORNER_SIZE, 214+CORNER_SIZE, 72-(CORNER_SIZE*2), CORNER_SIZE, color);

    // Shadow
    tft.fillRect(x, 214+CORNER_SIZE, CORNER_SIZE, CORNER_SIZE, shadowColor);
    tft.fillRect(x+72-CORNER_SIZE, 214+CORNER_SIZE, CORNER_SIZE, CORNER_SIZE, shadowColor);
    tft.fillRect(x+CORNER_SIZE, 214, 72-(CORNER_SIZE*2), CORNER_SIZE, shadowColor);
}

void Display::drawTabs() {
    drawTab(4, COLOR_BLUE, COLOR_BLUE_SHADOW);
    drawTab(84, COLOR_GREEN, COLOR_GREEN_SHADOW);
    drawTab(164, COLOR_PURPLE, COLOR_PURPLE_SHADOW);
    drawTab(244, COLOR_RED, COLOR_RED_SHADOW);
}

void Display::drawButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color, uint16_t shadowColor) {
    // drawDialog();

    // Button
    tft.fillRect(x, y, width, height, color);
    tft.fillRect(x, y+height, width, CORNER_SIZE, shadowColor);
    tft.fillRect(x, y+height+CORNER_SIZE, width, CORNER_SIZE, COLOR_DIALOG_SHADOW);

    tft.fillRect(x-CORNER_SIZE, y+CORNER_SIZE, CORNER_SIZE, height-CORNER_SIZE, color);
    tft.fillRect(x-CORNER_SIZE, y+height-CORNER_SIZE, CORNER_SIZE, CORNER_SIZE, shadowColor);
    tft.fillRect(x-CORNER_SIZE, y+height, CORNER_SIZE, CORNER_SIZE, COLOR_DIALOG_SHADOW);

    tft.fillRect(x+width, y+CORNER_SIZE, CORNER_SIZE, height-CORNER_SIZE, color);
    tft.fillRect(x+width, y+height-CORNER_SIZE, CORNER_SIZE, CORNER_SIZE, shadowColor);
    tft.fillRect(x+width, y+height, CORNER_SIZE, CORNER_SIZE, COLOR_DIALOG_SHADOW);
    
    // tft.setTextColor(COLOR_WHITE);
    // tft.setTextSize(4);
    // tft.setCursor(x+(width/2) - (2*24)-12, y+8+4);
    // tft.print("PS-01");
}

void Display::drawKnobPositions(uint16_t attack, uint16_t decay, uint8_t sustain, uint16_t release) {
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
