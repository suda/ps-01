#pragma once

#if !defined(PARTICLE)
#include "../vendor/Print.h"
#include "../vendor/WString.h"

typedef bool boolean;
#define delay(x) SDL_Delay(x)
#define millis() SDL_GetTicks()

#endif  // PARTICLE