#include "adsr.h"

ADSR::ADSR() { _oneMSf = float(ONE_MS); }

void ADSR::setAttack(uint16_t attack) { _attack = attack; }

void ADSR::setDecay(uint16_t decay) {
    _decay = decay;
    _decayf = float(_decay);
    _decayOneMSf = _decayf * ONE_MS;
}

void ADSR::setSustain(uint8_t sustain) {
    _sustain = sustain;
    _sustainf = float(_sustain) / float((1 << 8) - 1);
    _sustainInvf = 1.0f - _sustainf;
}

void ADSR::setRelease(uint16_t release) {
    _release = release;
    _releasef = float(release);
    _releaseOneMSf = _releasef * ONE_MS;
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
    switch (_state) {
        case ADSR_ATTACK:
            sample *= float(_clock) / float(_attack) / _oneMSf;
            break;
        case ADSR_DECAY:
            sample *=
                _sustainInvf * (_decayOneMSf - _clock) / _decayf / _oneMSf +
                _sustainf;
            break;
        case ADSR_SUSTAIN:
            sample *= _sustainf;
            break;
        case ADSR_RELEASE:
            sample *=
                _sustainf * (_releaseOneMSf - _clock) / _releasef / _oneMSf;
            break;
        default:
            return 0;
    }
    return sample;
}

void ADSR::debug() {}