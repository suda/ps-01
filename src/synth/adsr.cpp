#include "adsr.h"

ADSR::ADSR() {}

void ADSR::setAttack(uint16_t attack) {
    _attack = attack;
}

void ADSR::setDecay(uint16_t decay) {
    _decay = decay;
}

void ADSR::setSustain(uint8_t sustain) {
    _sustain = sustain;
}

void ADSR::setRelease(uint16_t release) {
    _release = release;
}

void ADSR::setGate(bool gate) {
    _gate = gate;
    _clock = 0;

    _state = _gate ? ADSR_ATTACK : ADSR_RELEASE;
}

void ADSR::clock() {
    _clock++;

    // Attack -> Decay -> Sustain -> Release cycle
    switch (_state) {
        case ADSR_ATTACK:
            if (_clock > ONE_MS * _attack) {
                _state = ADSR_DECAY;
                _clock = 0;
            }
            break;
        case ADSR_DECAY:
            if (_clock > ONE_MS * _decay) {
                _state = ADSR_SUSTAIN;
            }
            break;
        case ADSR_RELEASE:
            if (_clock > ONE_MS * _release) {
                _state = ADSR_IDLE;
            }
            break;
        default:
            break;
    }
}

int16_t ADSR::apply(int16_t sample) {
    float sustainValue = float(_sustain) / float((1 << 8) - 1);
    switch (_state) {
        case ADSR_ATTACK:
            sample *= float(_clock) / float(_attack) / float(ONE_MS);
            break;
        case ADSR_DECAY:
            sample *= (1.0f - sustainValue) * float((_decay * ONE_MS) - _clock) / float(_decay) / float(ONE_MS) + sustainValue;
            break;
        case ADSR_SUSTAIN:
            sample *= sustainValue;
            break;
        case ADSR_RELEASE:
            sample *= sustainValue * float((_release * ONE_MS) - _clock) / float(_release) / float(ONE_MS);
            break;
        default:
            return 0;
    }
    return sample;
}