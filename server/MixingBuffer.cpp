#include <MixingBuffer.h>
#include <Room.h>
#include <cstring>
#include <ServerManager.h>
#include <Room.h>
#include <Packet_v1_Jam.h>

MixingBuffer::MixingBuffer(ServerManager * serverManager, Room * room, std::size_t size)
  : _serverManager(serverManager), _room(room), _size(size)
{
  std::cout << "*** NEW MIXING ENGINE *** size = " << _size << std::endl;
  InitBuffer();
}

MixingBuffer::~MixingBuffer()
{
  delete[] _mixBuffer;
}

void		MixingBuffer::SendFrameToRoom(std::size_t idx)
{
  std::cout << "->      send frame to room" << std::endl;
  Room::m_session::const_iterator cit, cend = _room->getConnected()->end();

  // Create one packet only for everybody                          
  Packet_v1_Jam     *packet_v1_jam = new Packet_v1_Jam(JAM_RECV);
  packet_v1_jam->setAudio((byte_t const *)_mixBuffer[idx]._mixData, AUDIOBUFFER_MAXLEN);
  packet_v1_jam->setDeleteTTL(_room->size());

  for (cit = _room->getConnected()->begin(); cit != cend; ++cit)
    _serverManager->Send(packet_v1_jam, cit->second);
  ResetOne(_start);
  _start = (_start + 1) % _size;
  --_count;
}

bool		MixingBuffer::IsMixed(AudioFrame const * audioFrame, std::size_t idx) const
{
  assert(idx < _size &&
	 _mixBuffer[idx]._participantsMap.find(audioFrame->getSessionId())
	 != _mixBuffer[idx]._participantsMap.end());

  return (_mixBuffer[idx]._participantsMap.find(audioFrame->getSessionId())->second);
}

void		MixingBuffer::DropFrame(AudioFrame const *)
{
  ++_drop;
  return;
}

void		MixingBuffer::pushFrame(AudioFrame const *audioFrame)
{

  _mixMutex.lock();
  std::cout << "^^^^^pushFrame_start" << std::endl;
  Debug_Print();
  std::cout << "^^^^^pushFrame_start" << std::endl;
  std::size_t	pos = FindPosition(audioFrame);
  std::cout << "------------------------------> pos = " << pos << ", roomsize = " << _room->size()
	    << "BUFFER {s=" << _start << ", e=" << _end << ", c=" << _count << "}" << std::endl;
  std::size_t	count;

  if (pos == _size + 1)
    {
      DropFrame(audioFrame);
      _mixMutex.unlock();
      return;
    }
  if (!(count = CountMixed(pos)))
    {
      _end = (pos + 1) % _size;      // an empty pos is used thus => _end = (_end + 1) % _size
      ++_count;
      //     SET TIMER FOR THIS IDX so that if not full it will still send data after expiration
    }
  std::cout << "^^^^^pushFrame_after_countmixed" << std::endl;
  Debug_Print();
  std::cout << "^^^^^pushFrame_after_countmixed" << std::endl;

  Mix(pos, audioFrame);
  std::cout << "^^^^^pushFrame_after_mix" << std::endl;
  Debug_Print();
  std::cout << "^^^^^pushFrame_after_mix" << std::endl;

  if (count + 1 == _room->size())
    SendFrameToRoom(pos);
  _mixMutex.unlock();
}

void		MixingBuffer::InitBuffer()
{
  _start = 0;
  _end = 0;
  _count = 0;
  _drop = 0;
  _mixBuffer = new mixframe_container[_size];
  ResetAll();
} 

void		MixingBuffer::ResetOne(std::size_t idx)
{
  assert(idx < _size);

  Room::m_session::const_iterator	cit, cend = _room->getConnected()->end();  
  for (cit = _room->getConnected()->begin(); cit != cend; ++cit)
    _mixBuffer[idx]._participantsMap[cit->first] = 0;
  memset(_mixBuffer[idx]._mixData, 0, AUDIOBUFFER_MAXLEN);
  _mixBuffer[idx]._len = 0;
}

void		MixingBuffer::Debug_Print() const
{

  for (std::size_t idx = 0; idx < _size; ++idx)
    {
      std::cout << "   [" << idx << "]";
      m_participants const & m = _mixBuffer[idx]._participantsMap;

      m_participants::const_iterator cit, cend = m.end();
      for (cit = m.begin(); cit != cend; ++cit)
	std::cout << " {" << cit->first << ", " << cit->second << "}" << " ";
      std::cout << std::endl;
    }

}

void		MixingBuffer::ResetAll()
{
  for(std::size_t i = 0; i < _size; ++i)
    ResetOne(i);
}

void		MixingBuffer::Mix(std::size_t idx, AudioFrame const *audioFrame)
{
  // CORRECT THIS
  //assert(IsMixed(audioFrame, idx));

  std::size_t		len = audioFrame->getLen();
  audioData_t *		track1 = _mixBuffer[idx]._mixData;
  audioData_t const *	track2 = audioFrame->getAudioData();

  // APPLYING MIX + NORMALIZE FORMULA :    mix_norm(A, B) = A + B - A * B
  for (std::size_t i = 0; i < AUDIOBUFFER_MAXLEN; ++i)
    track1[i] = track1[i] + track2[i] - (track1[i] * track2[i]);
  _mixBuffer[idx]._participantsMap[audioFrame->getSessionId()] = audioFrame->getTimestamp();
}

std::size_t		MixingBuffer::getDropCount() const
{
  return _drop;
}

// try to find available pos in buffer
// if all full or newer frames present in buffer return _size + 1
std::size_t		MixingBuffer::FindPosition(AudioFrame const *audioFrame) const
{
  unsigned int		sessionId = audioFrame->getSessionId();
  std::size_t		timestamp = audioFrame->getTimestamp();
  std::size_t		i;
  
  for (i = 0; i < _count; ++i)
    {
      m_participants const & m = _mixBuffer[(_start + i) % _size]._participantsMap;
      assert(m.find(sessionId) != m.end()); // all participants map should have been properly initialized

      std::size_t cTimestamp = m.find(sessionId)->second;

      if (cTimestamp == 0)		// if not mixed then return current position
	return (_start + i) % _size;
      if (cTimestamp > timestamp)	// if list contains newer timestamps return false (_size + 1)
	return _size + 1;
    }
  if (_count < _size || i < _count)
    return (_start + i) % _size;
  else
    return (_size + 1);
}

std::size_t		MixingBuffer::CountMixed(std::size_t idx) const
{
  std::size_t		count = 0;
  m_participants const & m = _mixBuffer[idx]._participantsMap;

  std::cout << "[START] idx = " << idx << ", countmixed m.size() = [[[[[[[[[[ " << m.size() << " ]]]]]]]]]]" << std::endl;
  std::cout << "map addr = " << &m << std::endl;
  m_participants::const_iterator cit, cend = m.end();
  for (cit = m.begin(); cit != cend; ++cit)
    {
      std::cout << "{" << cit->first << ", " << cit->second << "}" << std::endl;
      if (cit->second)
	++count;
    }
  std::cout << "[END]" << std::endl;
  return count;
}
