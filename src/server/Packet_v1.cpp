#include <Packet_v1.h>

p1_field	 data_field;

Packet_v1::Packet_v1(boost::asio::ip::udp::endpoint *endpoint)
  : Packet(endpoint)
{

}

Packet_v1::~Packet_v1()
{}

void		Packet_v1::MakePacket()
{
  memcpy(_buffer, &data_field, 3);
}

field_t		Packet_v1::getType() const
{
  // 4 derniers de buffer[0] + 2 premiers de buffer[1]

  char b_type = _buffer->at(0);
  char e_type = _buffer->at(1);

  std::cout << (field_t)_buffer->at(0) << " : " << (field_t)_buffer->at(1) << std::endl;

  return ((b_type << PROTO_VERSION_SIZE)
	  + (e_type >> (sizeof_bin(e_type) - PROTO_VERSION_SIZE)))
	  >> (sizeof_bin(b_type) - TYPE_SIZE);
}

field_t		Packet_v1::getSessionId() const
{
//   char session = _buffer->at(1);

//   return session << 2 >> (sizeof_bin(session) - SESSION_ID_SIZE);

  // 6 derniers de buffer[1] + 8 de buffer[2] + 2 premiers de buffer[3]
  //return _buffer[0] >> sizeof_bin(_buffer[0] - SESSION_ID_SIZE);
  return 0;
}

field_t		Packet_v1::getDataLen() const
{
//   char datalen = buffer->at(3);

//   return datalen << 2 >> (sizeof_bin(datalen) - DATALEN_SIZE);
  // 6 derniers de buffer[3] + 8 buffer[4] + 2 premiers buffer[5]
  //return _buffer[0] >> sizeof_bin(_buffer[0] - DATALEN_SIZE);
  return 0;
}

void		Packet_v1::setType(field_t type)
{
  data_field.type = type;
  //  memcpy(_buffer, &data_field, 1);
  char proto = _buffer->at(0);

  proto = proto << 4 << 

}

void		Packet_v1::setSessionId(field_t session)
{
  data_field.session = session;
}

void		Packet_v1::setDataLen(field_t datalen)
{
  data_field.session = datalen;
}

//	     380 (16bits)		       209 (16bits)
// 0000 0001    0111 1100	       0000 0000   1101 0001
// buffer[0]	buffer[1]	       buffer[2]   buffer[3]
//    1		  124			0	     209
