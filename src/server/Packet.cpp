#include <Packet.h>

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

void				Packet::MakePacket()
{

}

field_t				Packet::getProtoVersion() const
{
  return _buffer[0] >> sizeof_bin(_buffer[0] - PROTO_VERSION_SIZE);
}

void				Packet::setProtoVersion(field_t version)
{
  p_field.proto = version;
  memcpy(_buffer, &p_field, 1);
}
