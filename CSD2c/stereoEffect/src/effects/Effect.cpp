#include "Effect.h"

Effect::Effect(unsigned long samplerate) :
    samplerate(samplerate)
{
    
}
Effect::~Effect() {}

float Effect::process(float input) {
    if (bypass) return input;
    float wetSignal = this->applyEffect(input) * drywetRatio;
    float drySignal = input * (1 - drywetRatio);
    return wetSignal + drySignal;
}

void Effect::setBypass(bool bypass) {
    this->bypass = bypass;
}

bool Effect::getBypass() {
    return this->bypass;
}