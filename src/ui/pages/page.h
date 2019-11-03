#pragma once

#include "../../util/types.h"
#include "../display.h"

#define ACTION_TICK           1
#define ACTION_PAGE_INIT      2
#define ACTION_KEY_DOWN       10
#define ACTION_KEY_UP         11
#define ACTION_ENCODER_CHANGE 12
#define ACTION_ST_NEXT        20
#define MK_ARGS(name, arg0, arg1, arg2, arg3) int16_t name[] = {arg0, arg1, arg2, arg3};
#define NO_ARGS(name) MK_ARGS(name, 0, 0, 0, 0)
#define STORE_ST_CURRENT_NOTE 1
#define STORE_ST_CURRENT_WAVE 2

#define KEYPAD_1              1
#define KEYPAD_2              2
#define KEYPAD_3              3
#define KEYPAD_4              4
#define KEYPAD_5              5
#define KEYPAD_6              6
#define KEYPAD_7              7
#define KEYPAD_8              8
#define KEYPAD_9              9
#define KEYPAD_10             10
#define KEYPAD_11             11
#define KEYPAD_12             12
#define KEYPAD_13             13
#define KEYPAD_14             14
#define KEYPAD_15             15
#define KEYPAD_16             16
#define KEY_BACK              17
#define KEY_VOL_PLUS          18
#define KEY_VOL_MINUS         19

#define ENCODER_BLUE          1
#define ENCODER_GREEN         2
#define ENCODER_PURPLE        3
#define ENCODER_RED           4

class Page {
    public:
        Page();
        void setup(Store &store, Store &previousStore, const Display &display);
        virtual void handleAction(uint8_t action, int16_t args[]) = 0;
        virtual void handleStoreUpdate(uint8_t storeKey) = 0;
    protected:
        Store *_store;
        Store *_previousStore;
        Display _display;
};