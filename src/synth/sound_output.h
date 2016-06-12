#ifndef SOUND_OUTPUT_H
#define SOUND_OUTPUT_H

#if !defined(PARTICLE)
#include <stdint.h>
#endif

// Base sound output interface.
class SoundOutput {
    public:
        virtual ~SoundOutput() {};

        virtual void setChannelValues(int16_t left, int16_t right) = 0;
};

#endif //SOUND_OUTPUT_H
