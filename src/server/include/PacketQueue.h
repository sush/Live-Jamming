#ifndef __PACKETQUEUE_H__
#define __PACKETQUEUE_H__

#include <list>

#include <Packet.h>

class PacketQueue
{
public:
  PacketQueue();
  virtual ~PacketQueue();
  void		PushPacket(Packet *);
  Packet *	PopPacket();
  int		getMaxSize() const;
  int		getSize() const;
  int		getCurrentSize() const;
  
private:
  typedef std::list<Packet *>	l_Packet;
  l_Packet::iterator		l_Packet_it;
  l_Packet::const_iterator	l_Packet_cit;

  l_Packet			*_packetList;
  unsigned int			_maxSize;
};


#endif // ! __PACKETQUEUE_H__
