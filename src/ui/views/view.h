#pragma once

#include "../../util/types.h"
#include "../display.h"
#include "../store.h"

class View {
   public:
    View();
    void setup(Store &store, Store &previousStore, const Display &display);
    virtual void handleAction(uint8_t action, int16_t args[]) = 0;
    virtual void handleStoreUpdate(uint8_t storeKey) = 0;

   protected:
    Store *_store;
    Store *_previousStore;
    Display _display;
};