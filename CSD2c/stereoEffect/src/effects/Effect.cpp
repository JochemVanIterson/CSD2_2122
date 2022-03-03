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

void Effect::setDryWetRatio(double drywetRatio)
{
    if (drywetRatio < 0 || drywetRatio > 1.0) return;
    this->drywetRatio = drywetRatio;
}

double Effect::getDryWetRatio()
{
    return this->drywetRatio;
}

void Effect::setBypass(bool bypass) {
    this->bypass = bypass;
}

bool Effect::getBypass() {
    return this->bypass;
}