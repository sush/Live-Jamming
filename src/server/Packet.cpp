#include <Packet.h>

Packet::Packet(buffer_t const *buffer, std::size_t len)
  :_buffer(buffer), _len(len)
{

}

Packet::~Packet()
{
  delete _buffer;
}

void	Packet::Print() const
{
  std::cout << "[packet] ";
  std::cout.write(_buffer->data(), _len);
  std::cout << " [" << _len << " bytes]" << std::endl;
}
