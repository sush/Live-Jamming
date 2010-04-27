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
  return getField(PROTO_PROTOVERSION_OFF, PROTO_PROTOVERSION_SIZE);
}

void				Packet::setProtoVersion(field_t version)
{
  setField(version, PROTO_PROTOVERSION_OFF, PROTO_PROTOVERSION_SIZE);
}

field_t					Packet::getField(unsigned int bin_offset, unsigned int bin_len) const
{
  field_t				value = 0;
  unsigned int				start_byte;
  unsigned int				end_byte;
  unsigned char				byte;
  
  start_byte = bin_offset / 8;
  end_byte = (bin_offset + bin_len) / 8;
  if ((bin_offset + bin_len) % 8 == 0)
    --end_byte;

  // byte1		byte2		byte3
  // xxxx.xxBB	      BBBB.BBBB		BBxx.xxxx
  // putting only data of start byte beginning at offset;
  byte = _buffer->at(start_byte) << (bin_offset % 8);
  byte = byte >> (bin_offset % 8);
  
  // 0000.00BB -> value;

  value = byte;
  if (start_byte == end_byte)
    return value >> (8 - ((bin_offset + bin_len) % 8));
  for (unsigned int i = start_byte + 1; i <= end_byte; ++i)
    {
      if (i < end_byte || (bin_offset + bin_len) % 8 == 0)
	value = (value << 8) + _buffer->at(i);
      else
	{
	  byte = _buffer->at(i) >> (8 - (bin_offset + bin_len) % 8);
	  value = (value << (bin_offset + bin_len) % 8) + byte;
	}
    }
  return value;
}

void					Packet::setField(field_t value, unsigned int bin_offset, unsigned int bin_len)
{
  unsigned int		start_byte, end_byte, tmp_val;
  unsigned char		save_before, save_after;

  if (!bin_len)  // bin_len = 0 nothing to set
    return;

  start_byte = bin_offset / 8;
  end_byte = (bin_offset + bin_len) / 8;
  if ((bin_offset + bin_len) % 8 == 0)
    --end_byte;
  
  // byte1		byte2		byte3
  // xxxx.xxBB	      BBBB.BBBB		BBxx.xxxx
  // putting only data of start byte beginning at offset;

  // zero other data of value
  value = value << (sizeof_bin(value) - bin_len);
  value = value >> (sizeof_bin(value) - bin_len);

  // THIS IS TO HELP IF YOU MODIFY THIS FUNCTION
  //
  // bin_offset % 8 = 6
  // 0000.00BB		BBBB.BBBB	BBxx.xxxx	xxxx.xxxx
  // << bin_offset % 8
  // BBBB.BBBB		BBBB.xxxx	xxxx.xx00	0000.0000
  // >> sizeof(value) - (bin_offset % 8)
  // 0000.0000		0000.0000	0000.0000	00BB.BBBB

  //					     <------ bin_len --->
  // xxxx.xxxx	      xxxx.xxxx		xxxx.BBBB	BBBB.BBBB
  // << sizeof(value) - bin_len
  // BBBB.BBBB	      BBBB.0000		0000.0000	0000.0000
  // >> sizeof(value) - (8 - bin_offset % 8)
  // 0000.0000	      0000.0000		0000.0000	0000.00BB
  /////////////////////////////////////////////////////

  // save only data of first byte before value (other bits are zero ed)
  // xxxx.xxBB
  save_before = _buffer->at(start_byte);
  save_before = save_before >> (8 - bin_offset % 8);
  save_before = save_before << (8 - bin_offset % 8);
  // xxxx.xx00

  // save data of last byte after value (other bits are zero ed)
  // BBBB.Bxxx
  save_after = _buffer->at(end_byte);
  if ((bin_offset + bin_len) % 8 == 0)
    save_after = 0;
  else
    {
      save_after = save_after << ((bin_offset + bin_len) % 8);
      save_after = save_after >> ((bin_offset + bin_len) % 8);
    }
  // 0000.0xxx

  // first byte = first byte bits of value + save_before
  tmp_val = value << (sizeof_bin(value) - bin_len);
  tmp_val = tmp_val >> (sizeof_bin(value) - (8 - bin_offset % 8));
  _buffer->at(start_byte) = save_before + tmp_val;

  // intermediate bytes
  for (unsigned int i = start_byte + 1; i < end_byte; ++i)
    {
      tmp_val = value << (sizeof_bin(value) - bin_len + (8 - bin_offset % 8) + 8 * (i - start_byte - 1));
      tmp_val = tmp_val >> (sizeof_bin(value) - 8);
      _buffer->at(i) = tmp_val;
    }

  // last byte = last bits of value + save_after
  //  tmp_val = value
  if ((bin_offset + bin_len) % 8 == 0)
    tmp_val = value << (sizeof_bin(value) - 8);
  else
    tmp_val = value << (sizeof_bin(value) - ((bin_offset + bin_len) % 8));
  tmp_val = tmp_val >> (sizeof_bin(value) - 8);//((bin_offset + bin_len) % 8 - (8 - (bin_offset + bin_len) % 8)));
  if (start_byte == end_byte)
    _buffer->at(end_byte) = save_before + tmp_val + save_after;
  else
    _buffer->at(end_byte) = tmp_val + save_after;
  // xxxx.xxBB
  // 00xx.xxxx
  // xxxx.xx00
}
