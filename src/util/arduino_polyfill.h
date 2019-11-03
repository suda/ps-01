#if !defined(PARTICLE)
#ifndef ARDUINO_POLYFILL_H
#define ARDUINO_POLYFILL_H

#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../vendor/Print.h"
#include "../vendor/WString.h"

typedef bool boolean;
#define delay(x) SDL_Delay(x)
#define millis() SDL_GetTicks()

#endif // ARDUINO_POLYFILL_H
#endif // PARTICLE