#pragma once
#include "Effect.h"
#include "../tools/circBuffer.h"
#include "../oscillators/waveforms/sine.h"

#define PI_2 6.28318530717959

/**
 * @brief Effect that works as a chorus
 * 
 */
class ChorusEffect : public Effect
{
public:
    /**
     * @brief Construct a new Chorus Effect
     * 
     * @param samplerate Samplerate of the project
     */
    ChorusEffect(unsigned long samplerate, float modDepth, float modFreq);
    ~ChorusEffect();

    /**
     * @brief Override applyEffect method
     *
     * @param input Input sample
     * @return Output sample
     */
    float applyEffect(float input) override;
    void setParameter(std::string key, std::string value) override;

private:
    CircBuffer buffer;
    Sine modOscillator;
    float modDepth;

    /**
     * @brief Function that calculates the amount of samples for a given miliseconds
     *
     * @param ms Input in miliseconds
     * @return output in samples
     */
    unsigned long ms2samples(double ms);
};

