#include "DelayEffect.h"

DelayEffect::DelayEffect(unsigned long samplerate, double delayTime, double feedback) : Effect(samplerate),
                                                                                        delayTime(delayTime),
                                                                                        feedback(feedback)
{
    this->setDelayTime(delayTime);
}

DelayEffect::~DelayEffect() {}

float DelayEffect::applyEffect(float input)
{
    float newSample = buffer.read();
    buffer.write(input + newSample * feedback);
    buffer.tick();

    return newSample;
}
unsigned long DelayEffect::ms2samples(double ms) {
    return (samplerate / 1000.0) * ms;
}

void DelayEffect::setDelayTime(double delayTime) {
    if (delayTime < 0) return;
    this->delayTime = delayTime;
    buffer.resetSize(ms2samples(delayTime) + 1);
    buffer.setDistanceRW(ms2samples(delayTime));
}
double DelayEffect::getDelayTime() {
    return delayTime;
}
void DelayEffect::setFeedback(double feedback) {
    if (feedback < 0.0 || feedback > 1.0) return;
    this->feedback = feedback;
}
double DelayEffect::getFeedback() {
    return feedback;
}