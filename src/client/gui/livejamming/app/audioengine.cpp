#include "audioengine.h"

#include <portaudiocpp/System.hxx>


/*
  TODO :
  * HANDLE ALL ERRORS WITH PORTAUDIO::EXCEPTION
 */

/*
  CONSTRUCTOR/DESTRUCTOR
 */

AudioEngine::AudioEngine() :
    _system(portaudio::System::instance())
{

}

AudioEngine::~AudioEngine(){
  portaudio::System::terminate();
}

/*
  PUBLIC METHODS
 */
void	AudioEngine::startRecording(){
/*
  TODO :
  * FIND A WAY TO OPEN AN INPUT STREAM ON THE DEFAULT INPUT DEVICE.
  * WRITE A CALLBACK TO READ THE DATA FROM THE INPUT STREAM.
  * PRINT THE AMOUT OF DATA RECEIVED FROM THE INPUT STREAM.
  * 
 */
}

/*
  PRIVATE METHODS
 */

//void	AudioEngine::initialize(){
//  portaudio::System::initialize();
//
//  _system = &(portaudio::System::instance());
//}

//void	AudioEngine::terminate(){
//  /*
//     TODO :
//     * TERMINATE ALL OPENED STREAMS.
//     * CLOSE ALL OPENED DEVICES.
//   */
//  _system->terminate();
//}
