#include "keypad_test_view.h"

KeypadTestView::KeypadTestView() : View() {}

void KeypadTestView::handleAction(uint8_t action, int16_t args[]) {
    switch (action)
    {
    case ACTION_VIEW_INIT:
        Synth::instance()->voices[0].setPulseWidth((1 << 15));
        Synth::instance()->voices[0].setADSR(200, 200, 1 << 6, 500);
        Synth::instance()->voices[0].setWaveform(WF_TRIANGLE);
    case ACTION_KEY_DOWN:
        Synth::instance()->voices[0].setFrequency(_scale[args[0] - 1]);
        Synth::instance()->voices[0].setGate(true);
        break;
    case ACTION_KEY_UP:
        Synth::instance()->voices[0].setGate(false);
        break;
    }
}

void KeypadTestView::handleStoreUpdate(uint8_t storeKey) {
}