#ifndef DAC_SOUND_OUTPUT_H
#define DAC_SOUND_OUTPUT_H

#include "sound_output.h"

#define CHANNEL_LEFT DAC1
#define CHANNEL_RIGHT DAC2

// Photon DAC sound output
class DacSoundOutput : SoundOutput {
    public:
        DacSoundOutput();
        virtual ~DacSoundOutput();
};

#endif //DAC_SOUND_OUTPUT_H
