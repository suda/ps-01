#include "view.h"

View::View() {}

void View::setup(Store &store, Store &previousStore, const Display &display) {
    this->_store = &store;
    this->_previousStore = &previousStore;
    this->_display = display;
}