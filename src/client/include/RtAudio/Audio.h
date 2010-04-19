#ifndef __AUDIO_H__
#define __AUDIO_H__

#include <RtAudio.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <map>

#if defined( __WINDOWS_ASIO__ ) || defined( __WINDOWS_DS__ )
#include <windows.h>
#define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds )
#else // Unix variant
#include <unistd.h>
#define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif

class Audio {
 public:
  Audio();
  ~Audio();
 private:
  RtAudio _audio;
};

#endif // !__AUDIO_H__
