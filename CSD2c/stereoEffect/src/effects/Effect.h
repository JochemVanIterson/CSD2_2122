#pragma once
#include <iostream>
#include "math.h"

#define PI_2 6.28318530717959

class Effect
{
public:
    /**
     * @brief Construct a new Effect object
     * @param samplerate Samplerate of the effect
     */
    Effect(unsigned long samplerate);
    virtual ~Effect();

    /**
     * @brief Function that calculates the effect sample. Also handles dry-wet ratio and bypass
     *
     * @param input Input value
     * @return Output value
     */
    float process(float input);
    /**
     * @brief Virtual function that does the actual modification
     * 
     * @param input Input value
     * @return Output value
     */
    virtual float applyEffect(float input) = 0;

    virtual void setParameter(std::string key, std::string value) = 0;
    void setBaseParameter(std::string key, std::string value);

    // getters and setters
    /**
     * @brief Set the Dry Wet Ratio
     * 
     * @param drywetRatio Must be between 0.0 and 1.0
     */
    void setDryWetRatio(double drywetRatio);
    double getDryWetRatio();
    void setBypass(bool bypass);
    bool getBypass();

protected:    
    double samplerate = 44100;

private:
    double drywetRatio = 1.0;
    bool bypass = false;
};
