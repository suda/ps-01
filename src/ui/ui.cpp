#include "ui.h"

UI::UI() {}

void UI::begin() {
    display.begin();
    initViews();
    MK_ARGS(args, 0, 0, 0, 0)
    dispatchAction(ACTION_VIEW_INIT, args);
}

void UI::update() {}

void UI::end() {
    display.end();
}

void UI::dispatchAction(uint8_t action, int16_t args[]) {
    scaleTestView.handleAction(action, args);
    // Copy the contents of the current store to know the difference
    // when firing a next action
    previousStore = store;
}

void UI::initViews() {
    scaleTestView = ScaleTestView();
    scaleTestView.setup(store, previousStore, display);
}