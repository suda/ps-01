#pragma once

#include "display.h"
// Include all pages
#include "views/scale_test_view.h"

class UI {
    public:
        UI();
        void begin();
        void update();
        void end();
        void dispatchAction(uint8_t action, int16_t args[]);

    private:
        void initViews();

        Display display;
        ScaleTestView scaleTestView;

        struct Store previousStore;
        struct Store store;
};