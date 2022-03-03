#include "GainEffect.h"

GainEffect::GainEffect(unsigned long samplerate, float amount) :
    Effect(samplerate)
{
    setAmount(amount);
}

GainEffect::~GainEffect() {}

void GainEffect::setAmount(float amount) {
    if (amount < 0.0 || amount > 1.0) return;
    this->amount = amount;
}

float GainEffect::getAmount() {
    return this->amount;
}

float GainEffect::applyEffect(float input) {
    return input * amount;
}