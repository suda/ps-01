#pragma once

#include "../../util/types.h"

#define ACTION_KEY_DOWN       1
#define ACTION_KEY_UP         2
#define ACTION_ENCODER_CHANGE 3
#define NO_ARGS               (uint16_t[4]){0, 0, 0, 0}
#define MK_ARGS               (arg0, arg1, arg2, arg3)((uint16_t[4]){arg0, arg1, arg2, arg3})

class Page {
    public:
        Page();
        void handleAction(uint8_t action, uint16_t args[]);
        void handleStoreUpdate(uint8_t storeKey);
};