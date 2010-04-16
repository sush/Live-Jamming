#include <Packet.h>

Packet::Packet(boost::asio::ip::udp::endpoint const * endpoint, buffer_t const *buffer, std::size_t len)
  :_endpoint(endpoint), _buffer(buffer), _len(len)
{

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

boost::asio::ip::udp::endpoint const &		Packet::getEndpoint() const
{
  return *_endpoint;
}
