#include "ui.h"

UI::UI() {}

void UI::begin() {
    display.begin();
    initPages();
    MK_ARGS(args, 0, 0, 0, 0)
    dispatchAction(ACTION_PAGE_INIT, args);
}

void UI::update() {}

void UI::end() {
    display.end();
}

void UI::dispatchAction(uint8_t action, uint16_t args[]) {
    scaleTestPage.handleAction(action, args);
    // Copy the contents of the current store to know the difference
    // when firing a next action
    previousStore = store;
}

void UI::initPages() {
    scaleTestPage = ScaleTestPage();
    scaleTestPage.setup(store, previousStore, display);
}