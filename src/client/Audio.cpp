#include <Audio.h>

Audio::Audio(){
}

Audio::~Audio(){
}

void					Audio::Init(){

  if(this->getDevices() < 0)
    std::cout << "No audio device found" << std::endl;
  
  /* if (is set configuration file){
     if (audio parameters in the configuration file are valide){
     load parameters
     }
     }
     else if(we can access to device parameters){
     set audio parameters to default device parameters
     }
     else
     error
   */
}

int					Audio::getDevices(){

  unsigned int	count = _audio.getDeviceCount();
  if(count < 1)
    return -1;
  for(unsigned int i = 0; i<count;i++){
    _devices.push_back(_audio.getDeviceInfo(i));
  }
  return 0;
}

void Audio::Clean(){

  if (_audio.isStreamOpen()) 
    _audio.closeStream();
  if (_inputData.buffer) 
    free(_inputData.buffer);
}

