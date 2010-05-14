#ifndef __AUDIO_H__
#define __AUDIO_H__

#include <fmod/fmod.hpp>
#include <fmod/fmod_errors.h>
#include <iostream>
#include <cstdlib>
#include <cstring>

/*
METHOD TO IMPLEMENT
+ Read from conf
+ Write to conf
+ Check conf
*/


class Audio 
{
 public:

  Audio();
  virtual ~Audio();
  void			ERRCHECK(FMOD_RESULT);
  void			Run();
  void			Init();
  void			Stop();

 private:
  
  FMOD::System		*_system;
  FMOD::Sound		*_sound;
  static FMOD::Channel	*_channel;
  FMOD_CREATESOUNDEXINFO _exinfo;
  FMOD_RESULT		_result;
  
  FMOD_MODE		_mode;
  int			_recorddriver,_playbackdriver;
  static bool		_state;
};

#endif // ! __AUDIO_H__
