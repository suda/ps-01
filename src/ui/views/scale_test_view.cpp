#include "scale_test_view.h"

float scale[] = {C4_HZ, D4_HZ, E4_HZ, F4_HZ, G4_HZ, A4_HZ, B4_HZ, C5_HZ};

ScaleTestView::ScaleTestView() : View() {}

void ScaleTestView::handleAction(uint8_t action, int16_t args[]) {
    switch (action) {
        case ACTION_VIEW_INIT:
            init();
            break;

        case ACTION_TICK:
            if (args[0] - _store->stLastTick > 1000) {
                _store->stLastTick = args[0];
                NO_ARGS(args)
                handleAction(ACTION_ST_NEXT, args);
            }
            break;

        case ACTION_ST_NEXT:
            _store->stCurrentNote++;
            if (_store->stCurrentNote > 7) {
                _store->stCurrentNote = 0;
            }

            handleStoreUpdate(STORE_ST_CURRENT_NOTE);
            break;

        case ACTION_ENCODER_CHANGE:
            if (args[0] == ENCODER_BLUE) {
                _store->stCurrentWaveform =
                    (Waveform)((uint8_t)_store->stCurrentWaveform + args[1]);

                if (_store->stCurrentWaveform == WF_TEST) {
                    _store->stCurrentWaveform = WF_TRIANGLE;
                }
                if (_store->stCurrentWaveform == WF_NOISE) {
                    _store->stCurrentWaveform = WF_PULSE;
                }
                handleStoreUpdate(STORE_ST_CURRENT_WAVE);
            }
            break;

        default:
            break;
    }
}
void ScaleTestView::init() {
    keys = 10;
    keyWidth = 18;
    width = keys * keyWidth;
    height = 64;
    x = 160 - (width / 2);
    y = 100;

    // Init display
    _display.clearScreen();
    _display.drawDialog();
    _display.drawTabs(String(""), String(""), String(""), String(""));
    _display.drawKeys(x, y, width, height, keyWidth, keys);
    drawWaveforms();
    _display.update();
    // Init synth
    Synth::instance()->voices[0].setPulseWidth((1 << 15));
    Synth::instance()->voices[0].setADSR(200, 200, 1 << 6, 500);

    handleStoreUpdate(STORE_ST_CURRENT_NOTE);
    handleStoreUpdate(STORE_ST_CURRENT_WAVE);
    Synth::instance()->voices[0].setGate(true);
}

void ScaleTestView::handleStoreUpdate(uint8_t storeKey) {
    if (storeKey == STORE_ST_CURRENT_NOTE) {
        Synth::instance()->voices[0].setFrequency(scale[_store->stCurrentNote]);
        // Redraw the previous one...
        _display.drawKey(x, y, height, keyWidth, _previousStore->stCurrentNote, COLOR_WHITE);
        // ...and draw the current one
        _display.drawKey(x, y, height, keyWidth, _store->stCurrentNote, COLOR_BLUE);
        _display.update();
    }
    if (storeKey == STORE_ST_CURRENT_WAVE) {
        Synth::instance()->voices[0].setWaveform(_store->stCurrentWaveform);
    }
}

void ScaleTestView::drawWaveforms() {
    uint8_t y2 = 42;
    uint8_t height2 = 8;
    uint8_t x2 = x + 18;

    // Square
    // _display.tft.fillRect(x, y2, 2, height2, COLOR_BLACK);
    // _display.tft.fillRect(x, y2, height2, 2, COLOR_BLACK);
    // _display.tft.fillRect(x + height2 - 2, y2, 2, height2, COLOR_BLACK);
    // _display.tft.fillRect(x + height2 - 2, y2 + height2 - 2, height2, 2,
    // COLOR_BLACK); _display.tft.fillRect(x + (height2 * 2) - 4, y2, 2,
    // height2, COLOR_BLACK);
    _display.drawButton(x2 - 8, y2 - 4, 40, 16, COLOR_GRAY, COLOR_GRAY_SHADOW);
    _display.tft.drawFastVLine(x2, y2, height2 / 2 + 1, COLOR_WHITE);
    _display.tft.drawFastHLine(x2, y2, 12, COLOR_WHITE);
    _display.tft.drawFastVLine(x2 + 12 - 1, y2, height2, COLOR_WHITE);
    _display.tft.drawFastHLine(x2 + 12 - 1, y2 + height2 - 1, 12, COLOR_WHITE);
    _display.tft.drawFastVLine(x2 + (12 * 2) - 2, y2 + (height2 / 2),
                               height2 / 2 + 1, COLOR_WHITE);

    // Saw
    x2 += 60;
    _display.drawButton(x2 - 8, y2 - 4, 40, 16, COLOR_GRAY, COLOR_GRAY_SHADOW);
    x2 -= 1;
    _display.tft.drawLine(x2, y2 + height2 - 1, x2 + (12) - 1, y2, COLOR_WHITE);
    _display.tft.drawFastVLine(x2 + 12, y2, height2 + 1, COLOR_WHITE);
    _display.tft.drawLine(x2 + 12, y2 + height2 - 1, x2 + (12 * 2) - 0, y2,
                          COLOR_WHITE);
    _display.tft.drawFastVLine(x2 + (12 * 2) + 1, y2, height2 + 1, COLOR_WHITE);
    // _display.tft.drawLine(x2, y2, x2 + height2 - 1, y2 + height2 - 1,
    // COLOR_BLACK); _display.tft.drawLine(x2, y2 + height2 - 1, x2 + height2 -
    // 1, y2, COLOR_BLACK); _display.tft.drawLine(x2 + 1, y2 + height2 - 1, x2 +
    // height2 , y2, COLOR_BLACK); _display.tft.drawLine(x2 + 2, y2 + height2 -
    // 1, x2 + height2 + 1, y2, COLOR_BLACK); _display.tft.fillRect(x2 +
    // height2, y2, 2, height2, COLOR_BLACK);

    // _display.tft.drawLine(x2 + height2, y2 + height2 - 1, x2 + (height2 * 2)
    // - 1, y2, COLOR_BLACK); _display.tft.drawLine(x2 + height2 + 1, y2 +
    // height2 - 1, x2 + (height2 * 2) , y2, COLOR_BLACK);
    // _display.tft.drawLine(x2 + height2 + 2, y2 + height2 - 1, x2 + (height2 *
    // 2) + 1, y2, COLOR_BLACK); _display.tft.fillRect(x2 + height2 + height2,
    // y2, 2, height2, COLOR_BLACK);

    // Triangle
    x2 += 61;
    _display.drawButton(x2 - 8, y2 - 4, 40, 16, COLOR_GREEN,
                        COLOR_GREEN_SHADOW);
    _display.tft.drawLine(x2, y2 + height2 - 1, x2 + height2 - 1, y2,
                          COLOR_WHITE);
    _display.tft.drawLine(x2 + height2 - 1, y2, x2 + (height2 * 2) - 1 - 1,
                          y2 + height2 - 1, COLOR_WHITE);
    _display.tft.drawLine(x2 + (height2 * 2) - 2, y2 + height2 - 1,
                          x2 + (height2 * 3) - 3, y2, COLOR_WHITE);
    // _display.tft.drawLine(x2 + height2 - 1, y2, x2 + (height2 * 2) - 1 - 1,
    // y2 + height2 - 1, COLOR_BLACK); _display.tft.drawLine(x2 + 1, y2 +
    // height2 - 1, x2 + height2 , y2, COLOR_BLACK); _display.tft.drawLine(x2,
    // y2 + height2 - 1, x2 + height2 - 1, y2, COLOR_BLACK);
    // _display.tft.drawLine(x2 + 1, y2 + height2 - 1, x2 + height2 , y2,
    // COLOR_BLACK); _display.tft.drawLine(x2 + 2, y2 + height2 - 1, x2 +
    // height2 + 1, y2, COLOR_BLACK);

    // _display.tft.drawLine(x2 + height2 - 1, y2, x2 + (height2 * 2) - 1 - 1,
    // y2 + height2 - 1, COLOR_BLACK); _display.tft.drawLine(x2 + height2 + 1 -
    // 1, y2, x2 + (height2 * 2)  - 1, y2 + height2 - 1, COLOR_BLACK);
    // _display.tft.drawLine(x2 + height2 + 2 - 1, y2, x2 + (height2 * 2) + 1 -
    // 1, y2 + height2 - 1, COLOR_BLACK);
}