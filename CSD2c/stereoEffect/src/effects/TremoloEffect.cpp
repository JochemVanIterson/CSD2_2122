#include "TremoloEffect.h"

TremoloEffect::TremoloEffect(unsigned long samplerate, float modDepth, float modFreq, TremoloEffect::WaveformType waveformType) : Effect(samplerate)
{
    setModDepth(modDepth);
    setModFreq(modFreq);
    setModWaveform(waveformType);
}

TremoloEffect::~TremoloEffect() {}

void TremoloEffect::setModDepth(float modDepth) {
    if (modDepth < 0.0 || modDepth > 1.0) return;
    this->modDepth = modDepth;
}

float TremoloEffect::getModDepth() {
    return this->modDepth;
}


void TremoloEffect::setModFreq(float modFreq) {
    if (modFreq < 0.0 || modFreq > samplerate * 0.5) return;
    this->modFreq = modFreq;
}
float TremoloEffect::getModFreq() {
    return this->modFreq;
}

void TremoloEffect::setModWaveform(TremoloEffect::WaveformType waveformType) {
    switch (waveformType){
    case WaveformType::SINE:
    {
        modOscillator = new Sine(samplerate, modFreq);
        break;
    }
    case WaveformType::SAW:
    {
        modOscillator = new Saw(samplerate, modFreq);
        break;
    }
    case WaveformType::SQUARE:
    {
        modOscillator = new Square(samplerate, modFreq);
        break;
    }
    case WaveformType::TRIANGLE:
    {
        modOscillator = new Triangle(samplerate, modFreq);
        break;
    }
    default:
        throw "Tremelo::Tremelo - incorrect waveformType.";
        break;
    }
}

float TremoloEffect::applyEffect(float input) {
    if (modOscillator == nullptr) return input;
    modOscillator->tick();
    float modSample = modOscillator->getSample() * 0.5 + 0.5;
    modSample *= modDepth;
    modSample += 1.0 - modDepth;
    return input * modSample;
}