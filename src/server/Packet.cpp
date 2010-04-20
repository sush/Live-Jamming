#include <Packet.h>

Packet::Packet(boost::asio::ip::udp::endpoint const * endpoint, buffer_t const *buffer, std::size_t len)
  :_buffer(buffer), _len(len), _endpoint(endpoint)
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

Packet::buffer_t const &	Packet::getData() const
{
  return *_buffer;
}

boost::asio::ip::udp::endpoint const &		Packet::getEndpoint() const
{
  return *_endpoint;
}

unsigned short int	Packet::getSessionId() const
{
   unsigned short int	res = 1;

   std::cout << "[0] = " <<  (int)(*_buffer)[0]
	     << " [1] = " << (int)(*_buffer)[1]
	     << std::endl;
   return res;
}
