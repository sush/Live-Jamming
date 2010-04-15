#include <PacketQueue.h>

PacketQueue::PacketQueue()
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
