#ifndef __PACKETQUEUE_H__
#define __PACKETQUEUE_H__

#include <iostream>
#include <boost/thread.hpp>
#include <list>

#include <Packet.h>

class PacketQueue
{
public:
  PacketQueue();
  virtual ~PacketQueue();
  void		PushPacket(Packet *);
  Packet *	PopPacket();
  std::size_t		getMaxSize() const;
  std::size_t		getSize() const;
  std::size_t		getPacketCount() const;
  
private:
  typedef std::list<Packet *>	l_Packet;
  l_Packet::iterator		l_Packet_it;
  l_Packet::const_iterator	l_Packet_cit;
  boost::mutex			_mutex;

  l_Packet			*_packetList;
  std::size_t			_maxSize; //max size of list
  std::size_t			_packetCount; //number of packets having been treated
};


#endif // ! __PACKETQUEUE_H__
