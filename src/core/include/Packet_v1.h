#ifndef __PACKET_V1_H__
#define __PACKET_V1_H__

#include <iostream>
#include <boost/asio.hpp>

#include <Packet.h>

class Packet_v1 : public Packet
{
public:
  Packet_v1(boost::asio::ip::udp::endpoint const *);
  virtual		~Packet_v1();
  void			MakePacket();

  void			Print() const;
  void			Print_v1() const;
  field_t		getRequestId() const;
  field_t		getComponentId() const;
  field_t		getSessionId() const;
  field_t		getDataLen() const;
  void			setRequestId(field_t);
  void			setComponentId(field_t);
  void			setSessionId(field_t);
  void			setDataLen(field_t);
  char *		getStartOfData();

private:
  
};

#endif // ! __PACKET_V1_H__
