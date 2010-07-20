#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <portaudiocpp/System.hxx>
#include <portaudiocpp/SystemDeviceIterator.hxx>
#include <portaudiocpp/Device.hxx>
#include <iostream>

class bidon
{
public:
    bidon()
    {
        portaudio::System::initialize();
        std::cout << "SYSTEM INITIALISED" << std::endl;
    }
};

class AudioEngine : public bidon
{
 public:
    AudioEngine();
    ~AudioEngine();
    void		startRecording();

    /*
      PRIVATE METHODS
     */
 private:
    void		initialize();
    void		terminate();
    /*
      PRIVATE VARIABLES
     */
 private:
    portaudio::System&	_system;
};

#endif // AUDIOENGINE_H
