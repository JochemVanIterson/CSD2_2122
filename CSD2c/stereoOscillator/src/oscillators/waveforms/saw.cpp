#include "saw.h"


// Constructor and destructor
Saw::Saw(double samplerate, double frequency) :
  Oscillator(samplerate, frequency)
{
}

Saw::~Saw()
{
}


void Saw::calculate()
{
  // calculate sample
  // NOTE: sin() method is not the most efficient way to calculate the sine value
  sample = phase*2 - 1;
}
