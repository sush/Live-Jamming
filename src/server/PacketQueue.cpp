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
  _packetList->push_back(packet);
  if (_packetList->size() > _maxSize)
    _maxSize = _packetList->size();
}

int		PacketQueue::getMaxSize() const
{
  return _maxSize;
}

int		PacketQueue::getSize() const
{
  return _packetList->size();
}

int		PacketQueue::getPacketCount() const
{
  return _packetCount;
}

Packet *	PacketQueue::PopPacket()
{
  ++_packetCount;
  Packet *	ret = _packetList->front();
  _packetList->pop_front();
  return ret;
}
