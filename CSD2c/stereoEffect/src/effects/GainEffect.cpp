#include "GainEffect.h"

GainEffect::GainEffect(unsigned long samplerate, float amount) :
    Effect(samplerate)
{
    setAmount(amount);
}

GainEffect::~GainEffect() {}

void GainEffect::setParameter(std::string key, std::string value) {
    if (key == "amount") {
        setAmount(std::stof(value));
    }
    else {
        setBaseParameter(key, value);
    }
}

void GainEffect::setAmount(float amount) {
    if (amount < 0.0 || amount > 1.0) throw "Value out of bounds (0 - 1)";
    this->amount = amount;
}

float GainEffect::getAmount() {
    return this->amount;
}

float GainEffect::applyEffect(float input) {
    return input * amount;
}