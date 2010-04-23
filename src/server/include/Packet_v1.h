#ifndef __PACKET_V1_H__
#define __PACKET_V1_H__

#include <iostream>
#include <boost/asio.hpp>

#include <Packet.h>

#define TYPE_SIZE 6
#define SESSION_ID_SIZE 16
#define DATALEN_SIZE 16

class Packet_v1 : public Packet
{
public:
  Packet_v1(boost::asio::ip::udp::endpoint *);
  virtual ~Packet_v1();
  void MakePacket();

  field_t	getType() const;
  field_t	getSessionId() const;
  field_t	getDataLen() const;
  void		setType(field_t);
  void		setSessionId(field_t);
  void		setDataLen(field_t);

private:
  
};

#endif // ! __PACKET_V1_H__
