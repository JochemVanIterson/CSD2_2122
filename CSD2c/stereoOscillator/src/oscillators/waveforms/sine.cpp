#include "sine.h"

// Constructor and destructor
Sine::Sine(double samplerate, double frequency):Oscillator(samplerate, frequency){

}

Sine::~Sine(){
}


void Sine::calculate(){
  sample = sin(phase * PI_2);
}
