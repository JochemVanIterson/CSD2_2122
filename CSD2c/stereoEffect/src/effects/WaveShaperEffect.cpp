#include "WaveShaperEffect.h"

WaveShaperEffect::WaveShaperEffect(unsigned long samplerate, float amount, WaveshapeType shape) : Effect(samplerate),
                                                                                                  amount(amount)
{
    genShape(shape);
}

WaveShaperEffect::~WaveShaperEffect() {}

float WaveShaperEffect::applyEffect(float input)
{
    float index = (input + 1.0) * 2048;
    // interpolate! index lies in between 2 indices
    int i = (int)index;
    float outputValue = buffer[i];

    return outputValue;
}

void WaveShaperEffect::genShape(WaveshapeType type)
{
    switch (type)
    {
    case WaveshapeType::LINEAR:
    {
        float halfResolution = WAVESHAPER_RESOLUTION / 2;
        for (int x = 0; x < WAVESHAPER_RESOLUTION; x++)
        {
            float normalValue = (x - halfResolution) / halfResolution;
            buffer[x] = normalValue;
        }
        break;
    }
    case WaveshapeType::ATAN:
    {
        float halfResolution = WAVESHAPER_RESOLUTION / 2;
        float normalizeFactor = 1.0f / atan(amount);

        for (int x = 0; x < WAVESHAPER_RESOLUTION; x++)
        {
            float normalValue = (x - halfResolution) / halfResolution;
            buffer[x] = normalizeFactor * atan(amount * normalValue);
        }
        break;
    }
    default:
        throw "WaveShaperEffect::WaveShaperEffect - incorrect WaveshapeType.";
        break;
    }
    BufferDebugger::writeToFile(buffer, WAVESHAPER_RESOLUTION, "output.csv");
}

float WaveShaperEffect::linMap(float input, int x1, int x2, float min, float max)
{
    return (min * (x2 - input) + max * (input - x1)) / (x2 - x1);
}