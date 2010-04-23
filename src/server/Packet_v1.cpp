#include <Packet_v1.h>

Packet_v1::Packet_v1(boost::asio::ip::udp::endpoint *endpoint)
  : Packet(endpoint)
{

}

Packet_v1::~Packet_v1()
{}

void		Packet_v1::MakePacket()
{
  //  memcpy(_buffer, &data_field, 3);
}

field_t		Packet_v1::getType() const
{
  // 4 derniers de buffer[0] + 2 premiers de buffer[1]
  unsigned char size = sizeof_bin(_buffer->at(1));

//   return ((b_type << PROTO_VERSION_SIZE)
// 	  + (e_type >> (sizeof_bin(e_type) - PROTO_VERSION_SIZE)))
// 	  >> (sizeof_bin(b_type) - TYPE_SIZE);

  unsigned char c;
  unsigned char d;

  // octet1	octet2
  // ....XXXX  YY......
  // XXXX0000
  // 00XXXX00  000000YY
  // 00XXXXYY

  c = _buffer->at(0);
  c = c << 4;
  std::cout << "00YYYY00 = " << (int)(unsigned char)c << std::endl;
  c = c >> 2;
  std::cout << "00YYYY00 = " << (int)(unsigned char)c << std::endl;

  d = (unsigned char)_buffer->at(1) >> 6;
  std::cout << "d = " << (int)(unsigned char)d << std::endl;

  return c + d;
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
  // size 6
  unsigned char size = sizeof_bin(_buffer->at(1));
  unsigned char c;
  unsigned char d;
  unsigned char type_c = type;

  // buffer[0] = [4 proto] [4 type]

  // octet1	octet2
  // XXXX....   ..YYYYYY
  // XXXX0000
  // 00XXXX00  000000YY
  // 00XXXXYY


  c = _buffer->at(0) >> 4; // 0000XXXX
  c = c << 4;              // XXXX0000
  
  d = _buffer->at(1) << 2; // YYYYYY00
  d = _buffer->at(1) >> 2; // 00YYYYYY

  _buffer->at(0) = c + (type_c >> 2);
  type_c = type_c << 6;
  _buffer->at(1) = d + type_c;
  std::cout << "[0] = " << (int) (unsigned char)_buffer->at(0) << " [1] = " << (int)(unsigned char)_buffer->at(1) << std::endl;
}





void		Packet_v1::setSessionId(field_t session)
{

}

void		Packet_v1::setDataLen(field_t datalen)
{

}

