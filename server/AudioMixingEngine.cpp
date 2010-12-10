#include <AudioMixingEngine.h>
#include <AudioFrame.h>
#include <MixingBuffer.h>
#include <Exception.h>
#include <ServerManager.h>
#include <Room.h>
#include <Packet_v1_Jam.h>

AudioMixingEngine::AudioMixingEngine(ServerManager * serverManager, Room *room)
  : _serverManager(serverManager), _room(room), _size(room->size()), _connected(room->getConnected())
{	
  std::cout << "*** AUDIO MIXING ENGINE ***" << std::endl;
  Init();
}

AudioMixingEngine::~AudioMixingEngine()
{
  delete _mixingBuffer;
}

void		AudioMixingEngine::Init()
{
  Room::m_session_cit	it, end = _connected->end();
  std::size_t	i;		
  
  _mixingBuffer = new MixingBuffer(_serverManager, _room, MIXBUFFER_SIZE);
  for (it = _connected->begin(), i = 0; it != end; ++it, ++i)
    _sepFrameMap[it->first] = new l_frame;
}




void	AudioMixingEngine::recvAudioData(Packet_v1_Jam const * p_jam)
{
  // add to user's frame list
  unsigned int		sid = p_jam->getSessionId();
  unsigned int		timestamp = p_jam->getTimestamp();
  audio_t		*audio = (audio_t *)p_jam->getAudio();
  std::size_t		audio_len = p_jam->getAudioDataLen();
  AudioFrame		*audioFrame;

  if (_sepFrameMap.find(sid) == _sepFrameMap.end()) // modified packet
    throw std::runtime_error(X_BADJAM);
  
  audioFrame = new AudioFrame(sid, audio, audio_len, timestamp);
  _sepFrameMap[sid]->push_back(audioFrame);
  _mixingBuffer->pushFrame(audioFrame);
}

std::size_t	AudioMixingEngine::getDropCount() const
{
  return _mixingBuffer->getDropCount();
}
