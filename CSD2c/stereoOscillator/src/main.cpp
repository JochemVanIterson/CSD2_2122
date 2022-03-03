#include <iostream>
#include <stdio.h>
#include <thread>


#include "jack/jack_module_stereo.h"
#include "tools/tools.h"

#include "oscillators/voice.h"

unsigned long chunksize = 256;

JackModuleStereo jack;
unsigned long samplerate = 44100; // default

bool running = true;

Voice* leftVoice;
Voice* rightVoice;

static void audioProcess() {
  float *inBuffer = new float[chunksize];
  float *outBuffer = new float[chunksize * 2];

  leftVoice = new Voice(samplerate, "sine");
  rightVoice = new Voice(samplerate, "fm");

  do {
    jack.readSamples(inBuffer,chunksize);
    for(unsigned int i=0; i<chunksize; i++) {
      // write sine output * amplitude --> to output buffer
      outBuffer[i * 2] = leftVoice -> getSample();
      outBuffer[i * 2 + 1] = rightVoice->getSample();
      // calculate next sample
      leftVoice->tick();
      rightVoice->tick();
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

  //keep the program running and listen for user input, q = quit
  std::cout << "Press 'q' when you want to quit the program." << std::endl;
  while (running){
    // Output prompt
    // Set terminal to raw mode
    std::system("stty raw");

    // Wait for single character
    char input = std::getchar();
    if(input=='q'){
      running = false;
    } else if(input=='z'){
      keyOctave--;
    } else if(input=='x'){
      keyOctave++;
    } else if(input=='1'){
      leftVoice->setType("sine");
    } else if(input=='2'){
      leftVoice->setType("saw");
    } else if(input=='3'){
      leftVoice->setType("square");
    } else if(input=='4'){
      leftVoice->setType("triangle");
    } else if(input=='5'){
      leftVoice->setType("fm");
    } else {
      int keymidiValue = Tools::keymidi(input);
      if(keymidiValue!=-1){
        leftVoice->noteOn((12 * keyOctave) + keymidiValue, .2, 200.);
        rightVoice->noteOn((12 * keyOctave) + keymidiValue + 4, .2, 200.);
      }
    }

    // Reset terminal to normal "cooked" mode
    std::system("stty cooked");
  }

  audioThread.join();
  jack.end();

  //end the program
  return 0;
} // main()
