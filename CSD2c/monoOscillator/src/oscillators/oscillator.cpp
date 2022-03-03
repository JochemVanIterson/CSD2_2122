#include "oscillator.h"

// Constructor and destructor
Oscillator::Oscillator(double samplerate, double frequency) :
  samplerate(samplerate),
  frequency(frequency),
  phase(0),
  stepSize(frequency / samplerate),
  sample(0)
{

}

Oscillator::~Oscillator(){
}

double Oscillator::getSample() { return sample; }

void Oscillator::tick(){
  // increase phase
  phase += stepSize;
  // wrap phase from 0 to 1
  if(phase >= 1) phase = phase - 1;

  // calculate new sample
  calculate();
}

void Oscillator::setFrequency(double frequency){
  // Check if new frequency is higher then 0 and lower then nyquist frequency
  if(frequency > 0 && frequency < 0.5 * samplerate) {
    this->frequency = frequency;
    this->stepSize = frequency / samplerate;
  }
}

double Oscillator::getFrequency(){
  return frequency;
}
