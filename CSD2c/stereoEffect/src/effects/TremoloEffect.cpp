#include "TremoloEffect.h"

TremoloEffect::TremoloEffect(unsigned long samplerate, float modDepth, float modFreq, TremoloEffect::WaveformType waveformType) : Effect(samplerate)
{
    setModDepth(modDepth);
    setModFreq(modFreq);
    setModWaveform(waveformType);
}

TremoloEffect::~TremoloEffect() {}

void TremoloEffect::setParameter(std::string key, std::string value)
{
    if (key == "modDepth") {
        setModDepth(std::stof(value));
    }
    else if (key == "modFreq") {
        setModFreq(std::stof(value));
    }
    else if (key == "modWaveform") {
        if (value == "sine") setModWaveform(WaveformType::SINE);
        else if (value == "saw") setModWaveform(WaveformType::SAW);
        else if (value == "square") setModWaveform(WaveformType::SQUARE);
        else if (value == "triangle") setModWaveform(WaveformType::TRIANGLE);
        else throw "Unknown waveform";
    }
    else {
        setBaseParameter(key, value);
    }
}

void TremoloEffect::setModDepth(float modDepth) {
    if (modDepth < 0.0 || modDepth > 1.0) throw "Value out of bounds (0 - 1)";
    this->modDepth = modDepth;
}

float TremoloEffect::getModDepth() {
    return this->modDepth;
}


void TremoloEffect::setModFreq(float modFreq) {
    if (modFreq < 0.0 || modFreq > samplerate * 0.5) throw "Value out of bounds (0 - samplerate * 0.5)";
    this->modFreq = modFreq;
}
float TremoloEffect::getModFreq() {
    return this->modFreq;
}

void TremoloEffect::setModWaveform(WaveformType waveformType) {
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