#ifndef _EMPTYEFFECT_H_
#define _EMPTYEFFECT_H_
#include "Effect.h"

#define PI_2 6.28318530717959

class GainEffect : public Effect
{
public:
    // Constructor and destructor
    GainEffect(unsigned long samplerate, float amount);
    ~GainEffect();

    // override applyEffect method
    float applyEffect(float input) override;

    void setAmount(float amount);
    float getAmount();

private:
    float amount = 1.0;
};

#endif
