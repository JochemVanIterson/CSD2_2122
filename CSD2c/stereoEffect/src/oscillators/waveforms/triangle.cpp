#include "triangle.h"


// Constructor and destructor
Triangle::Triangle(double samplerate, double frequency) :
  Oscillator(samplerate, frequency)
{
}

Triangle::~Triangle()
{
}


void Triangle::calculate()
{
  if(phase<.5){
    sample = phase;
  } else {
    sample = 1. - phase;
  }
  sample = sample*2-1;
}
