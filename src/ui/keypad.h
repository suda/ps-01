#pragma once

#if defined(PARTICLE)
  #include "Adafruit_Trellis.h"
#endif
#include "ui.h"
#include "store.h"
#include "dispatcher.h"
#include "../util/types.h"

class Keypad {
    public:
        Keypad();
        static Keypad *instance() {
            static Keypad k;
            return &k;
        }
        void begin(Dispatcher &dispatcher);
        void updateLight(uint8_t light, bool state);
#if defined(PARTICLE)
        void loop();
#else
        void handleKey(SDL_Event &event);
#endif
    private:
        Dispatcher *_dispatcher;
#if defined(PARTICLE)
        Adafruit_Trellis _matrix0;
        Adafruit_TrellisSet _trellis = Adafruit_TrellisSet(&_matrix0);
        Timer _keyUpTimer = Timer(50, _interruptCb, true);
        void _interrupt();
        static void _interruptCb();
        bool _updated = false;
        uint16_t _state = 0;
#endif
};