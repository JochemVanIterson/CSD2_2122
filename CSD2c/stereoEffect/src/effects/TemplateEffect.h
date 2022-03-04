#pragma once
#include "Effect.h"

#define PI_2 6.28318530717959

/**
 * @brief Basic effect that does nothing (ouput == input).
 *
 */
class TemplateEffect : public Effect
{
public:
    /**
     * @brief Construct a new empty Effect
     *
     * @param samplerate Samplerate of the project
     */
    TemplateEffect(unsigned long samplerate);
    ~TemplateEffect();

    /**
     * @brief override applyEffect method
     *
     * @param input Input sample
     * @return Output sample
     */
    float applyEffect(float input) override;
    void setParameter(std::string key, std::string value) override;

private:
};
