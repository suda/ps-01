#include "page.h"

Page::Page() {}

void Page::setup(Store &store, Store &previousStore, const Display &display) {
    this->_store = &store;
    this->_previousStore = &previousStore;
    this->_display = display;
}