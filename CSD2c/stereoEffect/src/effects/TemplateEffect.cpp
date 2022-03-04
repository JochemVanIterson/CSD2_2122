#include "TemplateEffect.h"

TemplateEffect::TemplateEffect(unsigned long samplerate) :
    Effect(samplerate)
{

}

TemplateEffect::~TemplateEffect() {}

float TemplateEffect::applyEffect(float input)
{
    return input;
}

void TemplateEffect::setParameter(std::string key, std::string value)
{
    if (false /*key == "amount"*/)
    {
        // setAmount(std::stof(value));
    }
    else
    {
        setBaseParameter(key, value);
    }
}