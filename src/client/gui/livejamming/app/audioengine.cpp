#include "audioengine.h"
#include <inputthread.h>
#include <outputthread.h>

class Component_Jam;

AudioEngine::AudioEngine(Component_Jam& jam_) :
        jam(jam_)
{

  inputThread = new InputThread();
  //outputThread = new OutputThread();
}

AudioEngine::~AudioEngine(){ //faire qq chose de + propre
    inputThread->terminate();
    delete inputThread;
    outputThread->terminate();
    delete outputThread;
}
