#include <Packet.h>

bit_field	p_field;

Packet::Packet(boost::asio::ip::udp::endpoint * endpoint, buffer_t *buffer, std::size_t len)
  :_buffer(buffer), _len(len), _endpoint(endpoint)
{}

Packet::Packet(boost::asio::ip::udp::endpoint * endpoint)
  :_endpoint(endpoint)
{}


Packet::~Packet()
{
  delete _endpoint;
  delete _buffer;
}

void	Packet::Print() const
{
  std::cout << "[packet] ";
  std::cout.write(_buffer->data(), _len);
  std::cout << " [" << _len << " bytes]" << std::endl;
}

int	Packet::getMaxSize() const
{
  return PACKET_MAXSIZE;
}

Packet::buffer_t const &	Packet::getData() const
{
  return *_buffer;
}

boost::asio::ip::udp::endpoint const &		Packet::getEndpoint() const
{
  return *_endpoint;
}

field_t				Packet::getProtoVersion() const
{
//   field_t proto = _buffer[0];
//   return proto >> (sizeof_bin(proto) - PROTO_VERSION_SIZE);
  return 0;
}

void				Packet::setProtoVersion(field_t version)
{
  p_field.proto = version;
  memcpy(_buffer, &p_field, 1);
}
