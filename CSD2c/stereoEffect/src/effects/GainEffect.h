#pragma once
#include "Effect.h"

#define PI_2 6.28318530717959

/**
 * @brief Effect that gains the output.
 * 
 */
class GainEffect : public Effect
{
public:
    /**
     * @brief Construct a new Gain Effect
     *
     * @param samplerate Samplerate of the project
     * @param amount Gain amount (must be between 0 and 1)
     */
    GainEffect(unsigned long samplerate, float amount);
    ~GainEffect();

    /**
     * @brief override applyEffect method
     *
     * @param input Input sample
     * @return Output sample
     */
    float applyEffect(float input) override;

    void setParameter(std::string key, std::string value) override;

    /**
     * @brief Set the gain amount (must be between 0 and 1)
     * 
     * @param amount
     */
    void setAmount(float amount);
    float getAmount();

private:
    float amount = 1.0;
};
