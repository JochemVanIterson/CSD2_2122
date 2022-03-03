#ifndef _FM_OSC_H_
#define _FM_OSC_H_
#include <iostream>
#include "math.h"
#include "../oscillator.h"

#define PI_2 6.28318530717959


class FMOsc : public Oscillator
{
public:
  // Constructor and destructor
  FMOsc(double samplerate, double frequency, double ratio, double factor);
  ~FMOsc();

  void setRatio(double ratio);
  void setFactor(double factor);

  // override calculate method
  void calculate();
  void tick();
  void setFrequency(double frequency);
private:
  double frequency_base;
  double frequency_fm;
  double phase_fm;
  double sample_fm;
  double ratio;
  double factor;
};

#endif
