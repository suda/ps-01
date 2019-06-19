#ifndef ADSR_H
#define ADSR_H

class ADSR {
    public:
        ADSR();
        ~ADSR();

        void setAttack(int8_t attack);
        void setDecay(int8_t decay);
        void setSustain(int8_t sustain);
        void setRelease(int8_t release);
        void setGate(bool gate);
        // Increase the ADSR clock by delta
        void clock(int16_t delta);
        // Apply ADSR and return the sample
        int16_t apply(int16_t sample);
};

#endif //ADSR_H
