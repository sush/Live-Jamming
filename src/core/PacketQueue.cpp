#include <PacketQueue.h>

PacketQueue::PacketQueue()
  :_maxSize(0), _packetCount(0)
{
  _packetList = new l_Packet;
}

PacketQueue::~PacketQueue()
{
  delete _packetList;
}

void		PacketQueue::PushPacket(Packet * packet)
{
  // LOCK
  _mutex.lock();
  _packetList->push_back(packet);
  if (_packetList->size() > _maxSize)
    _maxSize = _packetList->size();
  // UNLOCK
  _mutex.unlock();
}

std::size_t	PacketQueue::getMaxSize() const
{
  return _maxSize;
}

std::size_t	PacketQueue::getSize() const
{
  return _packetList->size();
}

std::size_t	PacketQueue::getPacketCount() const
{
  return _packetCount;
}

Packet *	PacketQueue::PopPacket()
{
  // LOCK
  _mutex.lock();
  ++_packetCount;
  Packet *	ret = _packetList->front();
  _packetList->pop_front();
  // UNLOCK
  _mutex.unlock();
  return ret;
}
