#ifndef _OSCILLATOR_H_
#define _OSCILLATOR_H_
#include <iostream>
#include "math.h"

#define PI_2 6.28318530717959


class Oscillator{
public:
  //Constructor and destructor
  Oscillator(double samplerate, double frequency);
  virtual ~Oscillator();

  //return the current sample
  double getSample();
  // go to next sample
  virtual void tick();
  //getters and setters
  virtual void setFrequency(double frequency);
  double getFrequency();

  //NOTE - do we need a setter for phase? for now -> not using one

protected:
  virtual void calculate() = 0;
  double samplerate;
  double frequency;
  double phase;
  double stepSize;
  double sample;
};

#endif
