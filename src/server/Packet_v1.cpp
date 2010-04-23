#include <Packet_v1.h>

b_field	 p1_field;

Packet_v1::Packet_v1(boost::asio::ip::udp::endpoint *endpoint)
  : Packet(endpoint)
{

}

Packet_v1::~Packet_v1()
{}

void		Packet_v1::MakePacket()
{
  memcpy(_buffer, &p1_field, 3);
}

field_t		Packet_v1::getType() const
{
  // 4 derniers de buffer[0] + 2 premiers de buffer[1]
  //return _buffer[0] >> sizeof_bin(_buffer[0] - TYPE_SIZE);
  return 0;
}

field_t		Packet_v1::getSessionId() const
{
  // 6 premiers de buffer[1] + 8 de buffer[2] + 2 de buffer[3]
  //return _buffer[0] >> sizeof_bin(_buffer[0] - SESSION_ID_SIZE);
  return 0;
}

field_t		Packet_v1::getDataLen() const
{
  // 6 buffer[3] + 8 buffer[4] + 2 buffer[5]
  //return _buffer[0] >> sizeof_bin(_buffer[0] - DATALEN_SIZE);
  return 0;
}

void		Packet_v1::setType(field_t type)
{
  p1_field.type = type;
}

void		Packet_v1::setSessionId(field_t session)
{
  p1_field.session = session;
}

void		Packet_v1::setDataLen(field_t datalen)
{
  p1_field.session = datalen;
}

//	     380 (16bits)		       209 (16bits)
// 0000 0001    0111 1100	       0000 0000   1101 0001
// buffer[0]	buffer[1]	       buffer[2]   buffer[3]
//    1		  124			0	     209
