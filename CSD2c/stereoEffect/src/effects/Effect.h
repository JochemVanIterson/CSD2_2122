#ifndef _EFFECT_H_
#define _EFFECT_H_
#include <iostream>
#include "math.h"

#define PI_2 6.28318530717959

class Effect
{
public:
    // Constructor and destructor
    Effect(unsigned long samplerate);
    virtual ~Effect();

    float process(float input);
    virtual float applyEffect(float input) = 0;

    // getters and setters
    // void setDryWetRatio(double drywetRatio);
    // double getDryWetRatio();
    void setBypass(bool bypass);
    bool getBypass();

protected:    
    double samplerate = 44100;

private:
    double drywetRatio = 1.0;
    bool bypass = false;
};

#endif
