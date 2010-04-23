#include <Packet.h>

Packet::Packet(boost::asio::ip::udp::endpoint * endpoint, buffer_t *buffer, std::size_t len)
  :_buffer(buffer), _len(len), _endpoint(endpoint)
{}

Packet::Packet(boost::asio::ip::udp::endpoint * endpoint)
  :_endpoint(endpoint)
{
  _buffer = new buffer_t;
}


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
  return _buffer->at(0) >> (sizeof_bin(_buffer->at(0)) - PROTO_VERSION_SIZE);
}

void				Packet::setProtoVersion(field_t version)
{
  char				size = sizeof_bin(_buffer->at(0));
  char				c;

  //save all bits not in version last 4 bits into c
  c = _buffer->at(0) << (size - PROTO_VERSION_SIZE);
  c = c >> (size - PROTO_VERSION_SIZE);
  //set 4 first bits of byte to version and copy back previous 4 bits
  _buffer->at(0) = (version << (size - PROTO_VERSION_SIZE)) + c;
}
