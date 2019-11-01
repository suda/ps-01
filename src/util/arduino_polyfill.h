#ifndef ARDUINO_POLYFILL_H
#define ARDUINO_POLYFILL_H

#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../vendor/WString.h"

class Print {
    public:
        void print(char *value);
        void print(uint16_t value);
};

typedef bool boolean;

#endif // ARDUINO_POLYFILL_H