#include <AudioFrame.h>
#include <cstring>

AudioFrame::AudioFrame(unsigned int sessionId, audioData_t const * audioData, std::size_t len, std::size_t timestamp)
  :_sessionId(sessionId), _len(len), _timestamp(timestamp)
{
  _audioData = new audioData_t[len];
  memcpy(_audioData, audioData, len);
}

AudioFrame::~AudioFrame()
{
  delete []_audioData;
}

unsigned int		AudioFrame::getSessionId() const
{
  return _sessionId;
}

audioData_t const *	AudioFrame::getAudioData() const
{
  return _audioData;
}

std::size_t		AudioFrame::getLen() const
{
  return _len;
}

std::size_t		AudioFrame::getTimestamp() const
{
  return _timestamp;
}
