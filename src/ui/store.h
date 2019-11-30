#pragma once

#include "../util/types.h"

// Action definitions
#define ACTION_TICK           1
#define ACTION_VIEW_INIT      2
#define ACTION_KEY_DOWN       10
#define ACTION_KEY_UP         11
#define ACTION_ENCODER_CHANGE 12
#define ACTION_ST_NEXT        20
// Args macros
#define MK_ARGS(name, arg0, arg1, arg2, arg3) \
    int16_t name[] = {arg0, arg1, arg2, arg3};
#define NO_ARGS(name) MK_ARGS(name, 0, 0, 0, 0)
// Store value change
#define STORE_ST_CURRENT_NOTE 1
#define STORE_ST_CURRENT_WAVE 2

struct Store {
    uint8_t volume;
    uint32_t tick;

    // ScaleTestPage
    uint32_t stLastTick;
    uint8_t stCurrentNote;
    Waveform stCurrentWaveform = WF_TRIANGLE;
};