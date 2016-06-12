#ifndef FILE_SOUND_OUTPUT_H
#define FILE_SOUND_OUTPUT_H

#include <stdio.h>
#include "sound_output.h"

class FileSoundOutput : SoundOutput {
    FILE *__file;

    public:
        FileSoundOutput();
        ~FileSoundOutput();

        void setChannelValues(int16_t left, int16_t right);
};

#endif //FILE_SOUND_OUTPUT_H
