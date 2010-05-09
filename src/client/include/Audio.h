#ifndef __AUDIO_H__
#define __AUDIO_H__

#include <RtAudio.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <map>

/* #if defined( __WINDOWS_ASIO__ ) || defined( __WINDOWS_DS__ ) */
/* #include <windows.h> */
/* #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds ) */
/* #else // Unix variant */
/* #include <unistd.h> */
/* #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) ) */
/* #endif */

typedef signed short  MY_TYPE;
struct InputData {
    MY_TYPE* buffer;
    unsigned long bufferBytes;
    unsigned long totalFrames;
    unsigned long frameCounter;
    unsigned int channels;
};

class Audio {
 public:
  Audio();
  ~Audio();
  void					Init();
  int					getDevices();
  void					Clean();
 private:
  RtAudio				_audio;
  std::vector<RtAudio::DeviceInfo>	_devices;
  InputData				_inputData;
  RtAudio::StreamParameters		_inputParams;
};

#endif // !__AUDIO_H__
