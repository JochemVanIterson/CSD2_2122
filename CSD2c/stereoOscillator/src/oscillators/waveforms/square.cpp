#include "square.h"


// Constructor and destructor
Square::Square(double samplerate, double frequency) :
  Oscillator(samplerate, frequency)
{
}

Square::~Square()
{
}


void Square::calculate()
{
  if(phase<.5)sample=-1;
  else if(phase>=.5)sample=1;
}
