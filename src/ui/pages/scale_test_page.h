#include "page.h"

#define STORE_KEYPAD 1

class ScaleTestPage : public Page {
    public:
        ScaleTestPage();
        void handleAction(uint8_t action, uint16_t args[]);
        void handleStoreUpdate(uint8_t storeKey);
};
