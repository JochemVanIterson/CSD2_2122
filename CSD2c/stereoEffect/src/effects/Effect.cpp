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

void Effect::setBaseParameter(std::string key, std::string value) {
    if (key == "dryWet") {
        setDryWetRatio(std::stof(value));
    }
    else if (key == "bypass") {
        setBypass(value == "on");
    }
    else {
        std::string message = "Unknown parameter: " + key;
        throw message;
    }
}

void Effect::setDryWetRatio(double drywetRatio)
{
    if (drywetRatio < 0 || drywetRatio > 1.0) throw "Value out of bounds (0 - 1)";
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