#ifndef _SQUARE_H_
#define _SQUARE_H_
#include <iostream>
#include "math.h"
#include "../oscillator.h"

#define PI_2 6.28318530717959


class Square : public Oscillator
{
public:
  // Constructor and destructor
  Square(double samplerate, double frequency);
  ~Square();

  // override calculate method
  void calculate();


};

#endif
