#include <iostream>
#include <stdio.h>
#include <thread>
#include <regex>

#include "jack/jack_module_stereo.h"
#include "tools/tools.h"

#include "oscillators/voice.h"
#include "effects/Effect.h"
#include "effects/GainEffect.h"
#include "effects/DelayEffect.h"
#include "effects/TremoloEffect.h"

JackModuleStereo jack;
unsigned long samplerate = 44100; // default
unsigned long chunksize = 256;

bool running = true;

Voice* voice;
Effect* effectLeft;
Effect* effectRight;

double noteDuration = 200.0;
std::string inputType = "mic";

static void audioProcess() {
  float *inBuffer = new float[chunksize];
  float *outBuffer = new float[chunksize * 2];

  voice = new Voice(samplerate, "sine");
  effectLeft = new TremoloEffect(samplerate, 0.5, 20, TremoloEffect::WaveformType::SINE);
  effectRight = new TremoloEffect(samplerate, 0.5, 20, TremoloEffect::WaveformType::SINE);

  effectLeft->setDryWetRatio(1.0);
  effectRight->setDryWetRatio(1.0);

  do {
    jack.readSamples(inBuffer,chunksize);
    for(unsigned int i=0; i<chunksize; i++) {
      // write oscillator output --> to output buffer
      if (inputType == "osc") {
        outBuffer[i * 2] = voice -> getSample();
        outBuffer[i * 2 + 1] = voice -> getSample();
      } else if (inputType == "mic") {
        outBuffer[i * 2] = inBuffer[i];
        outBuffer[i * 2 + 1] = inBuffer[i];
      } else {
        outBuffer[i * 2] = 0;
        outBuffer[i * 2 + 1] = 0;
      }

      // apply effect on output
      outBuffer[i * 2] = effectLeft->process(outBuffer[i * 2]);
      outBuffer[i * 2 + 1] = effectRight->process(outBuffer[i * 2 + 1]);

      voice->tick();
    }

    jack.writeSamples(outBuffer,chunksize*2);
  } while(running);
}

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

int keyOctave = 5;

int main(int argc,char **argv){
  // --------------------------------------- Parameters --------------------------------------- //
  Tools::init_rand();

  // --------------------------------------- Jack --------------------------------------- //
  jack.setNumberOfInputChannels(1);
  jack.setNumberOfOutputChannels(2);
  jack.init(argv[0]); // use program name as JACK client name
  jack.autoConnect();
  samplerate = jack.getSamplerate();

  std::thread audioThread(audioProcess);

  bool keyMidi = false;
  //keep the program running and listen for user input, q = quit
  // std::cout << "Press 'q' when you want to quit the program." << std::endl;
  while (running){
    // Output prompt

    // Wait for single character
    std::string input;
    std::cout << "> ";
    getline(std::cin, input);
    
    if (input == "quit" || input == "q" || input == "exit") running = false;
    else if(input=="transpose down") keyOctave--;
    else if (input == "transpose up") keyOctave++;
    else if (input.find("set oscillator ") != std::string::npos)
    {
      std::string type = std::regex_replace(input, std::regex("set oscillator "), "");
      std::cout << "Setting oscillator to " << type << std::endl;
      voice->setType(type);
    }
    else if (input.find("set input ") != std::string::npos)
    {
      std::string type = std::regex_replace(input, std::regex("set input "), "");
      std::cout << "Setting input to " << type << std::endl;
      inputType = type;
    }
    else if (input.find("set duration ") != std::string::npos)
    {
      std::string stateString = std::regex_replace(input, std::regex("set duration "), "");
      if (stateString == "inf") {
        stateString = "0.0";
      }
      double state = std::stod(stateString);
      std::cout << "Setting duration to " << state << std::endl;
      noteDuration = state;
    }
    else if (input.find("set feedback ") != std::string::npos)
    {
      std::string stateString = std::regex_replace(input, std::regex("set feedback "), "");
      float state = std::stof(stateString);
      std::cout << "Setting feedback to " << state << std::endl;
      ((DelayEffect *)effectLeft)->setFeedback(state);
      ((DelayEffect *)effectRight)->setFeedback(state);
    }
    else if (input.find("set bypass") != std::string::npos)
    {
      std::string stateString = std::regex_replace(input, std::regex("set bypass "), "");
      bool state = stateString == "on";

      effectLeft->setBypass(state);
      effectRight->setBypass(state);
      std::cout << "Effect is " << (state ? "" : "not ") << "bypassed" << std::endl;
    }
    else if (input == "keymidi") {
      std::cout << "Enabling key midi. Exit by typing 'q'" << std::endl;
      keyMidi = true;
      // Set terminal to raw mode
      std::system("stty raw");
      while (keyMidi) {
        char inputChar = std::getchar();
        if (inputChar == 'q') keyMidi = false;
        
        int keymidiValue = Tools::keymidi(inputChar);
        if (keymidiValue != -1)
        {
          if (noteDuration > 0)
            voice->noteOn((12 * keyOctave) + keymidiValue, .2, noteDuration);
          else
            voice->noteOn((12 * keyOctave) + keymidiValue, .2);
        }
      }
      // Reset terminal to normal "cooked" mode
      std::system("stty cooked");
    }
  }

  audioThread.join();
  jack.end();

  //end the program
  return 0;
} // main()
