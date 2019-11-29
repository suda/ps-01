#include "keypad_test_view.h"

KeypadTestView::KeypadTestView() : View() {}

void KeypadTestView::handleAction(uint8_t action, int16_t args[]) {
    switch (action)
    {
    case ACTION_VIEW_INIT:
        Synth::instance()->setupAllVoices(WF_TRIANGLE, 200, 200, 1 << 6, 500, (1 << 15));
        break;
    case ACTION_KEY_DOWN:
        Polyphony::instance()->startFrequency(_scale[args[0] - 1]);
        break;
    case ACTION_KEY_UP:
        Polyphony::instance()->stopFrequency(_scale[args[0] - 1]);
        break;
    }
}

void KeypadTestView::handleStoreUpdate(uint8_t storeKey) {
}