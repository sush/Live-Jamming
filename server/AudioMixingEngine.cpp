#include <AudioMixingEngine.cpp>

// PSEUDO CODE
/*
  ON NEW FRAME ARRIVAL

  ADD TO USER FRAME LIST
  IF newframe from that user IN mixbuffer
	IF newframe more recent than the first one in the mixbuffer
		ADD TO mixbuffer (if there's space ELSE DROP)
	ELSE
		DROP
  ELSE
	ADD to mixbuffer

////////

SEND ON either mixbuffer timer expiration
OR		mixbuffer full
 
*/
       

AudioMixingEngine::AudioMixingEngine(Room *room)
  :_size(room->size()), _connected(room->getConnected())
{
  Init();
}

AudioMixingEngine::~AudioMixingEngine()
{
  
}

void		AudioMixing::Init()
{
  m_session_cit	it, end = _connected->end();
  std::size	i;		
  
  for (it = _connected.begin(), i = 0; it != end; ++it, ++i)
    _sepFrameMap[it->first] = new l_frame;
    

}




void	AudioMixingEngine::AddFrame(audio_t *frame)
{
  
  
}

void    AudioMixingEngine::Mix(audio_t *audio_mixed, audio_t const *audio_channel, std::size_t len)
{
  for (size_t i = 0; i <len; ++i)
    audio_mixed[i] = audio_mixed[i] + audio_channel[i] - (audio_mixed[i] * audio_channel[i]);
}
