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
    uint16_t x = CORNER_SIZE * 2;
    uint16_t y = CORNER_SIZE * 4;
    uint16_t w = 320 - (CORNER_SIZE * 4);
    uint16_t h = 176;

    // Background
    tft.fillRect(x, y, w, h, COLOR_DIALOG);

    // Top
    tft.fillRect(x + CORNER_SIZE, y - CORNER_SIZE, w - (CORNER_SIZE * 2),
                 CORNER_SIZE, COLOR_DIALOG);
    tft.fillRect(x + (CORNER_SIZE * 2), y - (CORNER_SIZE * 2),
                 w - (CORNER_SIZE * 4), CORNER_SIZE, COLOR_DIALOG);

    // Bottom
    tft.fillRect(x + CORNER_SIZE, y + h, w - (CORNER_SIZE * 2), CORNER_SIZE,
                 COLOR_DIALOG);
    tft.fillRect(x, y + h, CORNER_SIZE, CORNER_SIZE, COLOR_DIALOG_SHADOW);
    tft.fillRect(x + w - CORNER_SIZE, y + h, CORNER_SIZE, CORNER_SIZE,
                 COLOR_DIALOG_SHADOW);
    tft.fillRect(x + (CORNER_SIZE * 2), y + h + CORNER_SIZE,
                 w - (CORNER_SIZE * 4), CORNER_SIZE, COLOR_DIALOG);
    tft.fillRect(x + CORNER_SIZE, y + h + CORNER_SIZE, CORNER_SIZE, CORNER_SIZE,
                 COLOR_DIALOG_SHADOW);
    tft.fillRect(x + w - (CORNER_SIZE * 2), y + h + CORNER_SIZE, CORNER_SIZE,
                 CORNER_SIZE, COLOR_DIALOG_SHADOW);
    tft.fillRect(x + (CORNER_SIZE * 2), y + h + (CORNER_SIZE * 2),
                 w - (CORNER_SIZE * 4), CORNER_SIZE, COLOR_DIALOG_SHADOW);
}

void Display::drawTab(uint16_t x, String label, uint16_t color, uint16_t shadowColor) {
    const uint16_t tabWidth = 72;
    tft.fillRect(x, 214 + (CORNER_SIZE * 2), tabWidth, 18, color);
    tft.fillRect(x + CORNER_SIZE, 214 + CORNER_SIZE, tabWidth - (CORNER_SIZE * 2),
                 CORNER_SIZE, color);

    // Shadow
    tft.fillRect(x, 214 + CORNER_SIZE, CORNER_SIZE, CORNER_SIZE, shadowColor);
    tft.fillRect(x + tabWidth - CORNER_SIZE, 214 + CORNER_SIZE, CORNER_SIZE,
                 CORNER_SIZE, shadowColor);
    tft.fillRect(x + CORNER_SIZE, 214, tabWidth - (CORNER_SIZE * 2), CORNER_SIZE,
                 shadowColor);

    // Label
    tft.setTextSize(2);

    int16_t _x, _y;
    uint16_t width, height;
    tft.getTextBounds(label, 0, 0, &_x, &_y, &width, &height);
    _x = x + ((tabWidth - width) / 2);
    tft.setCursor(_x + 1, 214 + (CORNER_SIZE * 2) + 1);
    tft.setTextColor(shadowColor);
    tft.print(label);

    tft.setTextColor(COLOR_WHITE);
    tft.setCursor(_x, 214 + (CORNER_SIZE * 2));
    tft.print(label);
}

void Display::drawTabs(String labelA, String labelB, String labelC, String labelD) {
    if (labelA != String("")) drawTab(4, labelA, COLOR_BLUE, COLOR_BLUE_SHADOW);
    if (labelB != String("")) drawTab(84, labelB, COLOR_GREEN, COLOR_GREEN_SHADOW);
    if (labelC != String("")) drawTab(164, labelC, COLOR_PURPLE, COLOR_PURPLE_SHADOW);
    if (labelD != String("")) drawTab(244, labelD, COLOR_RED, COLOR_RED_SHADOW);
}

void Display::drawButton(uint16_t x, uint16_t y, uint16_t width,
                         uint16_t height, uint16_t color,
                         uint16_t shadowColor) {
    // drawDialog();

    // Button
    tft.fillRect(x, y, width, height, color);
    tft.fillRect(x, y + height, width, CORNER_SIZE, shadowColor);
    tft.fillRect(x, y + height + CORNER_SIZE, width, CORNER_SIZE,
                 COLOR_DIALOG_SHADOW);

    tft.fillRect(x - CORNER_SIZE, y + CORNER_SIZE, CORNER_SIZE,
                 height - CORNER_SIZE, color);
    tft.fillRect(x - CORNER_SIZE, y + height - CORNER_SIZE, CORNER_SIZE,
                 CORNER_SIZE, shadowColor);
    tft.fillRect(x - CORNER_SIZE, y + height, CORNER_SIZE, CORNER_SIZE,
                 COLOR_DIALOG_SHADOW);

    tft.fillRect(x + width, y + CORNER_SIZE, CORNER_SIZE, height - CORNER_SIZE,
                 color);
    tft.fillRect(x + width, y + height - CORNER_SIZE, CORNER_SIZE, CORNER_SIZE,
                 shadowColor);
    tft.fillRect(x + width, y + height, CORNER_SIZE, CORNER_SIZE,
                 COLOR_DIALOG_SHADOW);

    // tft.setTextColor(COLOR_WHITE);
    // tft.setTextSize(4);
    // tft.setCursor(x+(width/2) - (2*24)-12, y+8+4);
    // tft.print("PS-01");
}

void Display::drawKnobPositions(uint16_t attack, uint16_t decay,
                                uint8_t sustain, uint16_t release) {
    // 320 / 4 = 80
    uint8_t radius = 32;
    uint8_t y = 128;
    uint8_t offset = 4;
    uint8_t textY = y + radius + (offset * 2);
    tft.fillRect(0, textY, 320, 16, COLOR_BG);
    tft.setTextSize(2);

    // tft.fillCircle(40+offset, y+offset, radius, COLOR_BLUE_SHADOW);
    // tft.fillCircle(40, y, radius, COLOR_BLUE);
    tft.setCursor(40 - radius, textY);
    tft.setTextColor(COLOR_BLUE);
    tft.print(attack);

    // tft.fillCircle(80+40+offset, y+offset, radius, COLOR_GREEN_SHADOW);
    // tft.fillCircle(80+40, y, radius, COLOR_GREEN);
    tft.setCursor(80 + 40 - radius, textY);
    tft.setTextColor(COLOR_GREEN);
    tft.print(decay);

    // tft.fillCircle((80*2)+40+offset, y+offset, radius, COLOR_PURPLE_SHADOW);
    // tft.fillCircle((80*2)+40, y, radius, COLOR_PURPLE);
    tft.setCursor((80 * 2) + 40 - radius, textY);
    tft.setTextColor(COLOR_PURPLE);
    tft.print(sustain);

    // tft.fillCircle((80*3)+40+offset, y+offset, radius, COLOR_RED_SHADOW);
    // tft.fillCircle((80*3)+40, y, radius, COLOR_RED);
    tft.setCursor((80 * 3) + 40 - radius, textY);
    tft.setTextColor(COLOR_RED);
    tft.print(release);
}

void Display::drawKeys(uint16_t x, uint16_t y, uint16_t width,
                       uint16_t height, uint8_t keyWidth, uint8_t keys) {
    tft.fillRect(x, y, width, height, COLOR_WHITE);
    tft.fillRect(x, y - CORNER_SIZE, width, CORNER_SIZE, COLOR_BLACK);
    tft.fillRect(x - CORNER_SIZE, y, CORNER_SIZE, height - CORNER_SIZE,
                 COLOR_BLACK);
    tft.fillRect(x, y + height - CORNER_SIZE, width, CORNER_SIZE, COLOR_BLACK);
    tft.fillRect(x + width, y, CORNER_SIZE, height - CORNER_SIZE, COLOR_BLACK);

    for (uint8_t i = 0; i < keys + 1; i++) {
        tft.drawFastVLine(x + (keyWidth * i), y, height, COLOR_BLACK);
        uint8_t j = i + 6;
        if ((j % 7 != 0) && ((j + 4) % 7 != 0)) {
            tft.fillRect(x + (keyWidth * i) - CORNER_SIZE, y, CORNER_SIZE * 2,
                         30, COLOR_BLACK);
        }
    }
}

void Display::drawKey(uint16_t x, uint16_t y, uint16_t height, uint8_t keyWidth, uint8_t key,
                      uint16_t color) {
    tft.fillCircle(x + (keyWidth * (key + 1)) + 9, y + height - 14, 4, color);
}