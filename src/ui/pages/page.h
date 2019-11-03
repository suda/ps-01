#pragma once

#include "../../util/types.h"
#include "../display.h"

#define ACTION_TICK           1
#define ACTION_PAGE_INIT      2
#define ACTION_KEY_DOWN       10
#define ACTION_KEY_UP         11
#define ACTION_ENCODER_CHANGE 12
#define ACTION_ST_NEXT        20
#define MK_ARGS(name, arg0, arg1, arg2, arg3) uint16_t name[] = {arg0, arg1, arg2, arg3};
#define NO_ARGS(name) MK_ARGS(name, 0, 0, 0, 0)
#define STORE_ST_CURRENT_NOTE 1

class Page {
    public:
        Page();
        void setup(Store &store, Store &previousStore, const Display &display);
        virtual void handleAction(uint8_t action, uint16_t args[]) = 0;
        virtual void handleStoreUpdate(uint8_t storeKey) = 0;
    protected:
        Store *_store;
        Store *_previousStore;
        Display _display;
};