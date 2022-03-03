#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
#include <iostream>
#include "math.h"
#include "../oscillator.h"

#define PI_2 6.28318530717959


class Triangle : public Oscillator
{
public:
  // Constructor and destructor
  Triangle(double samplerate, double frequency);
  ~Triangle();

  // override calculate method
  void calculate();


};

#endif
