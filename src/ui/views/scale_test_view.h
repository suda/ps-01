#include "view.h"
#include "../../synth/synth.h"

class ScaleTestView: public View {
    public:
        ScaleTestView();
        void handleAction(uint8_t action, int16_t args[]);
        void handleStoreUpdate(uint8_t storeKey);
    private:
        void init();
        void drawKeys();
        void drawKey(uint8_t key, uint16_t color);
        void drawWaveforms();
        uint8_t keys;
        uint8_t keyWidth;
        uint16_t width;
        uint16_t height;
        uint16_t x;
        uint16_t y;
};
