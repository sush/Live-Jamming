#ifndef __AUDIOFRAME_H__
#define __AUDIOFRAME_H__

class AudioFrame;

#include <iostream>

typedef float	audioData_t;

class AudioFrame
{
public:
  AudioFrame(unsigned int, audioData_t const *, std::size_t, std::size_t);
  virtual		~AudioFrame();

  unsigned int		getSessionId() const;
  audioData_t const *	getAudioData() const;
  std::size_t		getLen() const;
  std::size_t		getTimestamp() const;

private:
  unsigned int		_sessionId;
  audioData_t *		_audioData;
  std::size_t		_len;
  std::size_t		_timestamp; // just an incremental counter used to track frame order
};

#endif // ! __AUDIOFRAME_H__
