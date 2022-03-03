#pragma once
#include "Effect.h"
#include "../oscillators/oscillator.h"
#include "../oscillators/waveforms/sine.h"
#include "../oscillators/waveforms/saw.h"
#include "../oscillators/waveforms/square.h"
#include "../oscillators/waveforms/triangle.h"

#define PI_2 6.28318530717959

/**
 * @brief Effect that gains the output.
 * 
 */
class TremoloEffect : public Effect
{
public:
    enum WaveformType
    {
        SINE = 0, // ensure enum starts at 0
        SAW,
        SQUARE,
        TRIANGLE,
        SIZE // 3
    };
    /**
     * @brief Construct a new Tremolo Effect
     *
     * @param samplerate Samplerate of the project
     * @param modDepth Depth of the modulation (must be between 0 and 1)
     * @param modFreq Frequency of the modulation (must be between 0 and 1)
     * @param waveformType Waveform of the modulator
     */
    TremoloEffect(unsigned long samplerate, float modDepth, float modFreq, WaveformType waveformType = WaveformType::SINE);
    ~TremoloEffect();

    /**
     * @brief override applyEffect method
     *
     * @param input Input sample
     * @return Output sample
     */
    float applyEffect(float input) override;

    /**
     * @brief Set the gain amount (must be between 0 and 1)
     * 
     * @param amount
     */
    void setModDepth(float modDepth);
    float getModDepth();

    /**
     * @brief Set the frequency of the modulator (must be between 0 and 1)
     *
     * @param modFreq
     */
    void setModFreq(float modFreq);
    float getModFreq();

    void setModWaveform(WaveformType waveformType);

private:
    Oscillator *modOscillator = nullptr;
    float modFreq = 10.0;
    float modDepth = 0.5;
};
