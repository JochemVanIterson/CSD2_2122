#pragma once
#include "Effect.h"
#include "../tools/bufferDebugger.h"

#define PI_2 6.28318530717959
#define WAVESHAPER_RESOLUTION 4096

class WaveShaperEffect : public Effect
{
public:
    enum WaveshapeType
    {
        LINEAR = 0, // ensure enum starts at 0
        ATAN,
        SIZE // 3
    };
    /**
     * @brief Construct a new WaveShaper Effect
     *
     * @param samplerate Samplerate of the project
     */
    WaveShaperEffect(unsigned long samplerate, float amount, WaveshapeType shape);
    ~WaveShaperEffect();

    /**
     * @brief override applyEffect method
     *
     * @param input Input sample
     * @return Output sample
     */
    float applyEffect(float input) override;
    void setParameter(std::string key, std::string value) override;

    void setShape(WaveshapeType type);

private:
    float amount = 1;
    float buffer[WAVESHAPER_RESOLUTION];

    float linMap(float input, int x1, int x2, float min, float max);
};
