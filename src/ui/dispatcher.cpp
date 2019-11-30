#include "dispatcher.h"

Dispatcher::Dispatcher() {}

void Dispatcher::begin() {
    display.begin();
    initViews();
    MK_ARGS(args, 0, 0, 0, 0)
    dispatchAction(ACTION_VIEW_INIT, args);
}

void Dispatcher::update() {}

void Dispatcher::end() {
    display.end();
}

void Dispatcher::dispatchAction(uint8_t action, int16_t args[]) {
    // scaleTestView.handleAction(action, args);
    keypadTestView.handleAction(action, args);
    // Copy the contents of the current store to know the difference
    // when firing a next action
    previousStore = store;
}

void Dispatcher::initViews() {
    scaleTestView = ScaleTestView();
    scaleTestView.setup(store, previousStore, display);
    keypadTestView = KeypadTestView();
    keypadTestView.setup(store, previousStore, display);
    poliphonyTestView = PoliphonyTestView();
    poliphonyTestView.setup(store, previousStore, display);
}