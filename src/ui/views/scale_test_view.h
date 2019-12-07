#pragma once

#include "../../synth/synth.h"
#include "../store.h"
#include "view.h"

class ScaleTestView : public View {
   public:
    ScaleTestView();
    void handleAction(uint8_t action, int16_t args[]);
    void handleStoreUpdate(uint8_t storeKey);

   private:
    void init();
    void drawWaveforms();
    uint8_t keys;
    uint8_t keyWidth;
    uint16_t width;
    uint16_t height;
    uint16_t x;
    uint16_t y;
};
