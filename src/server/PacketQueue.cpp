#include <PacketQueue.h>

PacketQueue::PacketQueue()
  :_maxSize(0)
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

Packet *	PacketQueue::PopPacket()
{
  if (_packetList->size() > 0)
    {
      Packet *	ret = _packetList->front();
      _packetList->erase(_packetList->begin());
      return ret;
    }
  return 0;
}
