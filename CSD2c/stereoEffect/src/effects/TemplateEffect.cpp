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