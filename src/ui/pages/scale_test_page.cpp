#include "scale_test_page.h"

ScaleTestPage::ScaleTestPage() {}

void ScaleTestPage::handleAction(uint8_t action, uint16_t args[]) {
    switch (action)
    {
    case ACTION_KEY_DOWN:
        // Todo update store
        break;
    case ACTION_KEY_UP:
        // Todo update store
        break;
    
    default:
        break;
    }
}

void ScaleTestPage::handleStoreUpdate(uint8_t storeKey) {
    switch (storeKey)
    {
    case STORE_KEYPAD:
        // TODO: Redraw keypad
        break;
    
    default:
        break;
    }
}

