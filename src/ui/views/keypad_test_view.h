#pragma once

#include "view.h"
#include "../store.h"
#include "../../synth/synth.h"

class KeypadTestView : public View {
    public:
        KeypadTestView();
        void handleAction(uint8_t action, int16_t args[]);
        void handleStoreUpdate(uint8_t storeKey);
    private:
        float _scale[16] = {
            C4_HZ,
              C4S_HZ,
            D4_HZ,
              D4S_HZ,
            E4_HZ,
            F4_HZ,
              F4S_HZ,
            G4_HZ,
              G4S_HZ,
            A4_HZ,
              A4S_HZ,
            B4_HZ,
            C5_HZ,
              C5S_HZ,
            D5_HZ,
              D5S_HZ
        };
};
