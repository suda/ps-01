#pragma once

#include "../../sequencer/polyphony.h"
#include "../../synth/synth.h"
#include "../store.h"
#include "view.h"

class KeypadTestView : public View {
   public:
    KeypadTestView();
    void handleAction(uint8_t action, int16_t args[]);
    void handleStoreUpdate(uint8_t storeKey);

   private:
    void init();

    float _scale[16] = {
        C3_HZ,    // 1
         C4S_HZ,  // 2
        D3_HZ,    // 3
         D4S_HZ,  // 4
        E3_HZ,    // Q
        F3_HZ,    // W
         F3S_HZ,  // E
        G3_HZ,    // R
         G3S_HZ,  // A
        A3_HZ,    // S
         A3S_HZ,  // D
        B3_HZ,    // F
        C4_HZ,    // Z
         C4S_HZ,  // X
        D4_HZ,    // C
         D4S_HZ   // v
    };
    float _frequency;
    float _octave;
    bool _playing;
};
