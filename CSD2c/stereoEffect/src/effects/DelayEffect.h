#pragma once
#include "Effect.h"
#include "../tools/circBuffer.h"

#define PI_2 6.28318530717959

/**
 * @brief Effect that works as a (feedback delay)
 * 
 */
class DelayEffect : public Effect
{
public:
    /**
     * @brief Construct a new Delay Effect
     * 
     * @param samplerate Samplerate of the project
     * @param delayTime Delay time in miliseconds
     * @param feedback Feedback amount
     */
    DelayEffect(unsigned long samplerate, double delayTime, double feedback);
    ~DelayEffect();

    /**
     * @brief Override applyEffect method
     *
     * @param input Input sample
     * @return Output sample
     */
    float applyEffect(float input) override;

    /**
     * @brief Set the Delay Time.
     * Must be higher then 0. This function will delete and recreate the delay buffer.
     * 
     * @param delayTime in miliseconds
     */
    void setDelayTime(double delayTime);
    double getDelayTime();
    /**
     * @brief Set the Feedback.
     * Must be between 0.0 and 1.0
     * @param feedback
     */
    void setFeedback(double feedback);
    double getFeedback();

private:
    double delayTime = 0;
    double feedback = 0;
    CircBuffer buffer;
    
    /**
     * @brief Function that calculates the amount of samples for a given miliseconds
     * 
     * @param ms Input in miliseconds
     * @return output in samples
     */
    unsigned long ms2samples(double ms);
};

