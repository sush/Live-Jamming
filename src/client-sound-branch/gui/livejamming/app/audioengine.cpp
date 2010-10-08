#include "audioengine.h"
#include <inputthread.h>
#include <outputthread.h>

class Component_Jam;

AudioEngine::AudioEngine(Component_Jam& jam_) :
        jam(jam_),
        running(false)
{
  inputThread = new InputThread();
  //outputThread = new OutputThread();
}

AudioEngine::~AudioEngine(){ //faire qq chose de + propre
    //Send signal to inputthread to quit the thread
    inputThread->can_process = 0;
    inputThread->mutex.unlock();
    inputThread->condition.wakeAll();
    //inputThread->terminate(); //should not be used but used anywamy because can_process does not make thread return
    inputThread->wait();
    qDebug() << "DELETING INPUT THREAD";
    delete inputThread;
    qDebug() << "DONE";
    //outputThread->terminate();
    //delete outputThread;
}
