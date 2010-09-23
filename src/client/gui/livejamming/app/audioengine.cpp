#include "audioengine.h"

AudioEngine::AudioEngine(){
  inputThread = new InputThread();
  outputThread = new OutputThread();
}

AudioEngine::~AudioEngine(){
}


