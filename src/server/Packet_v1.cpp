#include <Packet_v1.h>

Packet_v1::Packet_v1(boost::asio::ip::udp::endpoint *endpoint)
  : Packet(endpoint)
{

}

Packet_v1::~Packet_v1()
{}

field_t		Packet_v1::getType() const
{
  return 0;
}

field_t		Packet_v1::getSessionId() const
{
  return 0;
}

field_t		Packet_v1::getDataLen() const
{
  return 0;
}

void		Packet_v1::setType(field_t)
{

}

//	     380 (16bits)		       209 (16bits)
// 0000 0001    0111 1100	       0000 0000   1101 0001
// buffer[0]	buffer[1]	       buffer[2]   buffer[3]
//    1		  124			0	     209

void		Packet_v1::setSessionId(field_t)
{
}

void		Packet_v1::setDataLen(field_t)
{
}
