#include "Audio.h"

FMOD::Channel  *Audio::_channel = 0;
bool Audio::_state = true;

Audio::Audio(){

}

Audio::~Audio(){}

void		Audio::ERRCHECK(FMOD_RESULT result){
  if (result != FMOD_OK){
    std::cout << "ERROR (" << result << ") : " << FMOD_ErrorString(result) << std::endl;
    exit(-1);
  }
}

void		Audio::Init(){
  /*It's a mess but read/write from configuration doesn't exist yet*/
  _recorddriver = 0;
  _playbackdriver = 0;
  _mode = FMOD_2D | FMOD_HARDWARE | FMOD_OPENUSER;

  _result = FMOD::System_Create(&_system);
  ERRCHECK(_result);

  _result = _system->setOutput(FMOD_OUTPUTTYPE_ALSA);
  ERRCHECK(_result);

  _result = _system->setDriver(0);
  ERRCHECK(_result);

  _result = _system->init(32, FMOD_INIT_NORMAL,0);
  ERRCHECK(_result);
  
  memset(&_exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));  
  _exinfo.cbsize           = sizeof(FMOD_CREATESOUNDEXINFO);
  _exinfo.numchannels      = 2;
  _exinfo.format           = FMOD_SOUND_FORMAT_PCM16;
  _exinfo.defaultfrequency = 44100;
  _exinfo.length           = 20000;

  _result = _system->createSound(0, _mode, &_exinfo, &_sound);
  ERRCHECK(_result);
  _result = _system->recordStart(_recorddriver, _sound, true);  
  ERRCHECK(_result);
  _sound->setMode(FMOD_LOOP_NORMAL);
  _result = _system->playSound(FMOD_CHANNEL_REUSE, _sound, false, &_channel);
  ERRCHECK(_result);
}


void	Audio::Run(){
  this->Init();

  do {
    _system->update();
  } while (_state);
  
  this->Stop();
}

void	Audio::Stop(){
  
  if (_channel){
    _channel->stop();
    _channel = 0;
  }

  _result = _sound->release();
  ERRCHECK(_result);
  
  _result = _system->release();
  ERRCHECK(_result);  
}
