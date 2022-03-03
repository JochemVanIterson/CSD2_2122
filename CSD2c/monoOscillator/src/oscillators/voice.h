#ifndef _VOICE_H_
#define _VOICE_H_

#include "oscillator.h"
#include "waveforms/sine.h"
#include "waveforms/saw.h"
#include "waveforms/square.h"
#include "waveforms/triangle.h"
#include "waveforms/fm_osc.h"

#include <cmath>
#include <string>
#include <chrono>
#include <thread>

class Voice {
public:
  Voice();
  Voice(double samplerate, std::string type);
  ~Voice();

  void setFrequency(double freq);
  double getFrequency();
  void setType(std::string type);

  void noteOn(int midiNote, double amplitude, double duration);
  void noteOn(int midiNote, double amplitude);
  void noteOn();
  void noteOff();

  // Parsed to *oscillator
  double getSample();
  void tick();

private:
  std::string type;
  Oscillator *oscillator;
  bool isPlaying = false;
  double amplitude = 0.;
  double samplerate;
  double frequency;
  double duration;
  double m2f(int midiNote);

  std::thread *noteOffThread;
  void noteOffThreadCallable();
};

#endif
