#include "scale_test_page.h"

float scale[] = { C4_HZ, D4_HZ, E4_HZ, F4_HZ, G4_HZ, A4_HZ, B4_HZ, C5_HZ };

ScaleTestPage::ScaleTestPage(): Page() {}

void ScaleTestPage::handleAction(uint8_t action, int16_t args[]) {
    switch (action)
    {
    case ACTION_PAGE_INIT:
        keys = 10;
        keyWidth = 18;
        width = keys * keyWidth;
        height = 64;
        x = 160 - (width / 2);
        y = 100;

        // Init display
        _display.clearScreen();
        _display.drawDialog();
        _display.drawTabs();
        drawKeys();
        _display.update();
        // Init synth
        Synth::instance()->voices[0].setPulseWidth((1 << 15));
        Synth::instance()->voices[0].setADSR(200, 200, 1 << 6, 500);
        
        handleStoreUpdate(STORE_ST_CURRENT_NOTE);
        handleStoreUpdate(STORE_ST_CURRENT_WAVE);
        Synth::instance()->voices[0].setGate(true);
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
            _store->stCurrentWaveform = (Waveform)((uint8_t)_store->stCurrentWaveform + args[1]);

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

void ScaleTestPage::handleStoreUpdate(uint8_t storeKey) {
    if (storeKey == STORE_ST_CURRENT_NOTE) {
        Synth::instance()->voices[0].setFrequency(scale[_store->stCurrentNote]);
        // Redraw the previous one...
        drawKey(_previousStore->stCurrentNote, COLOR_WHITE);
        // ...and draw the current one
        drawKey(_store->stCurrentNote, COLOR_BLUE);
        _display.update();
    }
    if (storeKey == STORE_ST_CURRENT_WAVE) {
        Synth::instance()->voices[0].setWaveform(_store->stCurrentWaveform);
    }
}

void ScaleTestPage::drawKeys() {
    _display.tft.fillRect(x, y, width, height, COLOR_WHITE);
    _display.tft.fillRect(x, y - CORNER_SIZE, width, CORNER_SIZE, COLOR_BLACK);
    _display.tft.fillRect(x - CORNER_SIZE, y, CORNER_SIZE, height - CORNER_SIZE, COLOR_BLACK);
    _display.tft.fillRect(x, y + height - CORNER_SIZE, width, CORNER_SIZE, COLOR_BLACK);
    _display.tft.fillRect(x + width, y, CORNER_SIZE, height - CORNER_SIZE, COLOR_BLACK);

    for (uint8_t i=0; i<keys+1; i++) {
        _display.tft.drawFastVLine(x + (keyWidth * i), y, height, COLOR_BLACK);
        uint8_t j = i + 6;
        if ((j % 7 != 0) && ((j+4) % 7 != 0)) {
            _display.tft.fillRect(x + (keyWidth * i) - CORNER_SIZE, y, CORNER_SIZE * 2, 30, COLOR_BLACK);
        }
    }
}

void ScaleTestPage::drawKey(uint8_t key, uint16_t color) {
    _display.tft.fillCircle(
        x + (keyWidth * (key + 1)) + 9,
        y + height - 14,
        4,
        color
    );
}