#include "ChorusEffect.h"

ChorusEffect::ChorusEffect(unsigned long samplerate, float modDepth, float modFreq) : Effect(samplerate),
                                                                                      buffer(samplerate, 0),
                                                                                      modOscillator(samplerate, modFreq),
                                                                                      modDepth(modDepth)
{

}

ChorusEffect::~ChorusEffect() {}

float ChorusEffect::applyEffect(float input)
{
    buffer.write(input);
    buffer.setDistanceRW(modDepth * (modOscillator.getSample() * 0.5 + 0.5));

    float newSample = buffer.read();
    buffer.tick();
    modOscillator.tick();

    return newSample;
}
unsigned long ChorusEffect::ms2samples(double ms) {
    return (samplerate / 1000.0) * ms;
}