#include "keypad.h"

Keypad::Keypad() {
#if defined(PARTICLE)
    // _matrix0 = Adafruit_Trellis();
    // _trellis = Adafruit_TrellisSet(&_matrix0);
    // _keyUpTimer = Timer(50, _interruptCb, true);

    Wire.setSpeed(CLOCK_SPEED_400KHZ);
    pinMode(KEYPAD_INT_PIN, INPUT_PULLUP);
    attachInterrupt(KEYPAD_INT_PIN, _interruptCb, CHANGE);
    _trellis.begin(0x70);
#endif
}

void Keypad::begin(Dispatcher &dispatcher) { this->_dispatcher = &dispatcher; }

void Keypad::updateLight(uint8_t light, bool state) {
#if defined(PARTICLE)
    state ? _trellis.setLED(light) : _trellis.clrLED(light);
#endif
}

#if defined(PARTICLE)
void Keypad::_interruptCb() {
    auto self = Keypad::instance();
    self->_interrupt();
}

void Keypad::_interrupt() { _updated = true; }

void Keypad::loop() {
    if (_updated) {
        if (_trellis.readSwitches()) {
            bool keypadChanged = false;
            bool anyKeyPressed = false;
            for (uint8_t i = 0; i < 16; i++) {
                bool state = _trellis.isKeyPressed(i);
                anyKeyPressed |= state;
                if (state != BIT_CHECK(_state, i)) {
                    // State changed
                    keypadChanged = true;

                    if (state) {
                        BIT_SET(_state, i);
                    } else {
                        BIT_CLEAR(_state, i);
                    }
                }
            }

            if (keypadChanged) {
                _trellis.writeDisplay();
            }

            // This is silly but necessary. HT16K33 doesn't trigger interrup
            // on key up so we need to check manually with a timer
            if (anyKeyPressed) {
                _keyUpTimer.reset();
            }
        } else {
            _keyUpTimer.reset();
        }
        _updated = false;
    }
}
#else
void Keypad::handleKey(SDL_Event &event) {
    /*
        Key mapping

        Keypad:
        [1] [2] [3] [4]
        [Q] [W] [E] [R]
        [A] [S] [D] [F]
        [Z] [X] [C] [V]

        Encoders:
        [9] [0]
        [O] [P]
        [L] [;]
        [.] [/]

        Others:
        [-] Vol -
        [+] Vol +
        [Esc] Back
    */
    int16_t key = 0;
    switch (event.key.keysym.scancode) {
        // Keypad
        case SDL_SCANCODE_1:
            key = KEYPAD_1;
            break;
        case SDL_SCANCODE_2:
            key = KEYPAD_2;
            break;
        case SDL_SCANCODE_3:
            key = KEYPAD_3;
            break;
        case SDL_SCANCODE_4:
            key = KEYPAD_4;
            break;
        case SDL_SCANCODE_Q:
            key = KEYPAD_5;
            break;
        case SDL_SCANCODE_W:
            key = KEYPAD_6;
            break;
        case SDL_SCANCODE_E:
            key = KEYPAD_7;
            break;
        case SDL_SCANCODE_R:
            key = KEYPAD_8;
            break;
        case SDL_SCANCODE_A:
            key = KEYPAD_9;
            break;
        case SDL_SCANCODE_S:
            key = KEYPAD_10;
            break;
        case SDL_SCANCODE_D:
            key = KEYPAD_11;
            break;
        case SDL_SCANCODE_F:
            key = KEYPAD_12;
            break;
        case SDL_SCANCODE_Z:
            key = KEYPAD_13;
            break;
        case SDL_SCANCODE_X:
            key = KEYPAD_14;
            break;
        case SDL_SCANCODE_C:
            key = KEYPAD_15;
            break;
        case SDL_SCANCODE_V:
            key = KEYPAD_16;
            break;
        // Other keys
        case SDL_SCANCODE_ESCAPE:
            key = KEY_BACK;
            break;
        case SDL_SCANCODE_MINUS:
            key = KEY_VOL_MINUS;
            break;
        case SDL_SCANCODE_EQUALS:
            key = KEY_VOL_PLUS;
            break;
        default:
            break;
    }

    if (key) {
        uint8_t action =
            event.type == SDL_KEYDOWN ? ACTION_KEY_DOWN : ACTION_KEY_UP;
        MK_ARGS(args, key, 0, 0, 0)
        _dispatcher->dispatchAction(action, args);
        return;
    }
    if (event.type != SDL_KEYUP) {
        return;
    }
    int16_t encoder = 0;
    int16_t change = 0;
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_9:
            encoder = ENCODER_BLUE;
            change = -1;
            break;
        case SDL_SCANCODE_0:
            encoder = ENCODER_BLUE;
            change = 1;
            break;
        case SDL_SCANCODE_O:
            encoder = ENCODER_GREEN;
            change = -1;
            break;
        case SDL_SCANCODE_P:
            encoder = ENCODER_GREEN;
            change = 1;
            break;
        case SDL_SCANCODE_L:
            encoder = ENCODER_PURPLE;
            change = -1;
            break;
        case SDL_SCANCODE_SEMICOLON:
            encoder = ENCODER_PURPLE;
            change = 1;
            break;
        case SDL_SCANCODE_PERIOD:
            encoder = ENCODER_RED;
            change = -1;
            break;
        case SDL_SCANCODE_SLASH:
            encoder = ENCODER_RED;
            change = 1;
            break;
        default:
            break;
    }
    if (encoder) {
        MK_ARGS(args, encoder, change, 0, 0)
        _dispatcher->dispatchAction(ACTION_ENCODER_CHANGE, args);
        return;
    }

    printf("Key not mapped: %s\n",
           SDL_GetScancodeName(event.key.keysym.scancode));
}
#endif