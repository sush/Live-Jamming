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
  void			PlayOutput(FMOD::Sound *);
  FMOD::Sound *		RecordInput();
  void			ERRCHECK(FMOD_RESULT);

 private:

  FMOD::System		*_system;
  FMOD::Sound		*_sound;
  FMOD::Channel		*_channel;
  FMOD_RESULT		_result;
};

#endif // ! __AUDIO_H__
