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
  //  std::cout.write(_buffer->data(), _len);
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

field_t					getField(unsigned int bin_offset, unsigned int bin_len) const
{
  field_t				value = 0;
  unsigned int				start_byte;
  unsigned int				end_byte;
  unsigned char				byte;
  
  start_byte = bin_offset / 8;
  end_byte = start_byte + bin_len / 8;

  // byte1		byte2		byte3
  // xxxx.xxBB	      BBBB.BBBB		BBxx.xxxx
  // putting only data of start byte beginning at offset;
  byte = _buffer->at(start_byte) << (bin_offset % sizeof(byte));
  byte = byte >> (bin_offset % 8);
  // 0000.00BB -> value;

  value = byte;
  for (int i = start_byte + 1; i <= end_byte; ++i)
    {
      byte = buffer->at(i);
      byte = byte >> (8 - (bin_offset + bin_len) % 8);
      value = value << (8 - (bin_offset + bin_len) % 8) + byte;
    }
  std::cout << "value = " << value << std::endl;
}

void					setField(field_t value, unsigned int bin_offset, unsigned int bin_len)
{
  unsigned char				save_before_start;
  unsigned char				save_after_end;
  
  start_byte = bin_offset / 8;
  end_byte = start_byte + bin_len / 8;
  
  // do we have data to save before start_byte;
  // do we have data to save after end_byte;
  

}
