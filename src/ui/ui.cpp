#include "ui.h"

UI::UI() {}

void UI::begin() {
#if defined(PARTICLE)
    this->tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
#else
    this->tft = Adafruit_SDL();
#endif

    this->tft.begin();
    this->clearScreen();
    // drawButton();
#if !defined(PARTICLE)
    this->tft.update();
#endif

    this->initPages();
}

void UI::update() {

}

void UI::end() {
#if !defined(PARTICLE)
    this->tft.end();
#endif
}

void UI::initPages() {
    this->scaleTestPage = ScaleTestPage();

    this->currentPage = this->scaleTestPage;
}

void UI::clearScreen() {
#if defined(PARTICLE)
    this->tft.setRotation(3);
#endif
    this->tft.fillScreen(COLOR_BG);
}

void UI::drawButton() {
    uint8_t corner = 4;
    uint8_t width = 160;
    uint8_t height = 48;
    uint8_t x = 80;
    uint8_t y = 70;

    // Dialog
    this->tft.fillRect(50, 30, 220, 180, COLOR_DIALOG);

    // Top
    this->tft.fillRect(50+corner, 30-corner, 220-(corner*2), corner, COLOR_DIALOG);
    this->tft.fillRect(50+(corner*2), 30-(corner*2), 220-(corner*4), corner, COLOR_DIALOG);

    // Bottom
    this->tft.fillRect(50+corner, 210, 220-(corner*2), corner, COLOR_DIALOG);
    this->tft.fillRect(50, 210, corner, corner, COLOR_DIALOG_SHADOW);
    this->tft.fillRect(50+220-corner, 210, corner, corner, COLOR_DIALOG_SHADOW);
    this->tft.fillRect(50+(corner*2), 210+corner, 220-(corner*4), corner, COLOR_DIALOG);
    this->tft.fillRect(50+corner, 210+corner, corner, corner, COLOR_DIALOG_SHADOW);
    this->tft.fillRect(50+220-(corner*2), 210+corner, corner, corner, COLOR_DIALOG_SHADOW);
    this->tft.fillRect(50+(corner*2), 210+(corner*2), 220-(corner*4), corner, COLOR_DIALOG_SHADOW);

    // Button
    this->tft.fillRect(x, y, width, height, COLOR_BLUE);
    this->tft.fillRect(x, y+height, width, corner, COLOR_BLUE_SHADOW);
    this->tft.fillRect(x, y+height+corner, width, corner, COLOR_DIALOG_SHADOW);

    this->tft.fillRect(x-corner, y+corner, corner, height-corner, COLOR_BLUE);
    this->tft.fillRect(x-corner, y+height-corner, corner, corner, COLOR_BLUE_SHADOW);
    this->tft.fillRect(x-corner, y+height, corner, corner, COLOR_DIALOG_SHADOW);

    this->tft.fillRect(x+width, y+corner, corner, height-corner, COLOR_BLUE);
    this->tft.fillRect(x+width, y+height-corner, corner, corner, COLOR_BLUE_SHADOW);
    this->tft.fillRect(x+width, y+height, corner, corner, COLOR_DIALOG_SHADOW);
    
    this->tft.setTextColor(COLOR_WHITE);
    this->tft.setTextSize(4);
    this->tft.setCursor(x+(width/2) - (2*24)-12, y+8+4);
    this->tft.print("PS-01");
}

void UI::drawKnobPositions(uint16_t attack, uint16_t decay, uint8_t sustain, uint16_t release) {
    // 320 / 4 = 80
    uint8_t radius = 32;
    uint8_t y = 128;
    uint8_t offset = 4;
    uint8_t textY = y+radius+(offset*2);
    this->tft.fillRect(0, textY, 320, 16, COLOR_BG);
    this->tft.setTextSize(2);

    // this->tft.fillCircle(40+offset, y+offset, radius, COLOR_BLUE_SHADOW);
    // this->tft.fillCircle(40, y, radius, COLOR_BLUE);
    this->tft.setCursor(40-radius, textY);
    this->tft.setTextColor(COLOR_BLUE);
    this->tft.print(attack);

    // this->tft.fillCircle(80+40+offset, y+offset, radius, COLOR_GREEN_SHADOW);
    // this->tft.fillCircle(80+40, y, radius, COLOR_GREEN);
    this->tft.setCursor(80+40-radius, textY);
    this->tft.setTextColor(COLOR_GREEN);
    this->tft.print(decay);

    // this->tft.fillCircle((80*2)+40+offset, y+offset, radius, COLOR_PURPLE_SHADOW);
    // this->tft.fillCircle((80*2)+40, y, radius, COLOR_PURPLE);
    this->tft.setCursor((80*2)+40-radius, textY);
    this->tft.setTextColor(COLOR_PURPLE);
    this->tft.print(sustain);

    // this->tft.fillCircle((80*3)+40+offset, y+offset, radius, COLOR_RED_SHADOW);
    // this->tft.fillCircle((80*3)+40, y, radius, COLOR_RED);
    this->tft.setCursor((80*3)+40-radius, textY);
    this->tft.setTextColor(COLOR_RED);
    this->tft.print(release);
}