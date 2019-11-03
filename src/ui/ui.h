#pragma once

#include "display.h"
// Include all pages
#include "pages/scale_test_page.h"

class UI {
    public:
        UI();
        void begin();
        void update();
        void end();
        void dispatchAction(uint8_t action, uint16_t args[]);

    private:
        void initPages();

        Display display;
        ScaleTestPage scaleTestPage;

        struct Store previousStore;
        struct Store store;
};