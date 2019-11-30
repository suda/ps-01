#pragma once

#include "display.h"
#include "store.h"
// Include all pages
#include "views/scale_test_view.h"
#include "views/keypad_test_view.h"
#include "views/poliphony_test_view.h"

class Dispatcher {
    public:
        Dispatcher();
        void begin();
        void update();
        void end();
        void dispatchAction(uint8_t action, int16_t args[]);

    private:
        void initViews();

        Display display;
        ScaleTestView scaleTestView;
        KeypadTestView keypadTestView;
        PoliphonyTestView poliphonyTestView;

        struct Store previousStore;
        struct Store store;
};