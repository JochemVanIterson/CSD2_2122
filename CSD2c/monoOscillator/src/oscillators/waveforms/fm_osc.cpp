#include "fm_osc.h"

// Constructor and destructor
FMOsc::FMOsc(double samplerate, double frequency, double ratio, double factor):
  Oscillator(samplerate, frequency),
  phase_fm(0),
  sample_fm(0)
{
  this->ratio = ratio;
  this->factor = factor;
}

FMOsc::~FMOsc(){
}


void FMOsc::calculate(){
  sample = sin(phase * PI_2);
  sample_fm = sin(phase_fm * PI_2);
  Oscillator::setFrequency(frequency_base * ( (sample_fm*factor)+1 ) );

}
void FMOsc::tick(){
  // increase phase
  phase_fm += frequency_fm / samplerate;
  // wrap phase from 0 to 1
  if(phase_fm >= 1) phase_fm = phase_fm - 1;

  Oscillator::tick();
}

void FMOsc::setFrequency(double frequency){
  if(frequency > 0 && frequency < 0.5 * samplerate){
    frequency_base = frequency;
    frequency_fm = frequency*ratio;
    Oscillator::setFrequency(frequency);
  }
}

void FMOsc::setRatio(double ratio){
  this->ratio = ratio;
  setFrequency(frequency);
}
void FMOsc::setFactor(double factor){
  this->factor = factor;
}
