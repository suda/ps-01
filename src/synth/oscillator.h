#ifndef OSCILLATOR_H
#define OSCILLATOR_H

class Oscillator {
    public:
        Oscillator();
        ~Oscillator();

        void setWaveform(int8_t waveform);
        void setFrequency(int16_t frequency);
        void setPulseWidth(int8_t pulseWidth);
        // Increase the oscillator clock by delta
        void clock(int16_t delta);
        // Get the resulting sample
        int16_t getOutput();
};

#endif //OSCILLATOR_H
