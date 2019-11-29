#pragma once

#include "view.h"
#include "../store.h"
#include "../../synth/synth.h"
#include "../../sequencer/polyphony.h"

class KeypadTestView : public View {
    public:
        KeypadTestView();
        void handleAction(uint8_t action, int16_t args[]);
        void handleStoreUpdate(uint8_t storeKey);
    private:
        float _scale[16] = {
            C4_HZ,    // 1
              C4S_HZ, // 2
            D4_HZ,    // 3
              D4S_HZ, // 4
            E4_HZ,    // Q
            F4_HZ,    // W
              F4S_HZ, // E
            G4_HZ,    // R
              G4S_HZ, // A
            A4_HZ,    // S
              A4S_HZ, // D
            B4_HZ,    // F
            C5_HZ,    // Z
              C5S_HZ, // X
            D5_HZ,    // C
              D5S_HZ  // v
        };
};
