#include "file_sound_output.h"

FileSoundOutput::FileSoundOutput() {
    __file = fopen("output.pcm", "w+");
}

FileSoundOutput::~FileSoundOutput() {
    fclose(__file);
}

void FileSoundOutput::setChannelValues(int16_t left, int16_t right) {
    fwrite(&left, sizeof(int16_t), 1, __file);
    fwrite(&right, sizeof(int16_t), 1, __file);
}