#include <Packet.h>
#include <stdexcept>

Packet::Packet(boost::asio::ip::udp::endpoint const * endpoint, buffer_t *buffer, std::size_t len)
  :_buffer(buffer), _len(len), _endpoint(endpoint)
{
  for (std::size_t i = len; i < PACKET_MAXSIZE; ++i)
    _buffer->at(i) = '\0';
}

Packet::Packet(boost::asio::ip::udp::endpoint const * endpoint)
  :_len(BINARYTOBYTE_LEN(PROTO_PROTOVERSION_SIZE)), _endpoint(endpoint)
{
  _buffer = new buffer_t;
  for (std::size_t i = 0; i < PACKET_MAXSIZE; ++i)
    _buffer->at(i) = '\0';
}

Packet::Packet()
  :_len(BINARYTOBYTE_LEN(PROTO_PROTOVERSION_SIZE)), _endpoint(0)
{
  std::cout << "<<<<<<< HERE HERE HERE >>>>>>>>>>>>>" << std::endl;
  _buffer = new buffer_t;
  for (std::size_t i = 0; i < PACKET_MAXSIZE; ++i)
    _buffer->at(i) = '\0';
}

Packet::~Packet()
{
  delete _endpoint;
  delete _buffer;
}

void	Packet::Print(std::string const &, Manager const *) const
{
  std::cout << PACKET_STRING << " [Packet] " << PACKET_STRING << std::endl;
  Print_base();
  std::cout << PACKET_STRING << PACKET_STRING << PACKET_STRING << std::endl;
}


void	Packet::Print_base() const
{
  std::cout << "REAL_LEN = " << _len << std::endl;
  std::cout << "[PROTO_VERSION: " << getProtoVersion() << " {" << PROTO_PROTOVERSION_SIZE << "}]"
	    << "[DATALEN: " << getDataLen() << " {" << PROTO_DATALEN_SIZE << "}]"
	    << std::endl;
}

int	Packet::getMaxSize() const
{
  return PACKET_MAXSIZE;
}

Packet::buffer_t const &	Packet::getRawData() const
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

std::size_t			Packet::getLen() const
{
  return _len;
}

void				Packet::setProtoVersion(field_t version)
{
  setField(version, PROTO_PROTOVERSION_OFF, PROTO_PROTOVERSION_SIZE);
}

void				Packet::setLen(std::size_t len)
{
  _len = len;
}

void				Packet::addLen(std::size_t len)
{
  _len += len;
}

field_t					Packet::getField(unsigned int bin_offset, unsigned int bin_len) const
{
  field_t				value = 0;
  unsigned int				start_byte;
  unsigned int				end_byte;
  byte_t				byte;
  
  //  std::cout << "[0] " << (int)_buffer->at(0) << " [1] " << (int)_buffer->at(1) << std::endl;

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
  //  std::cout << "value = " << value << std::endl;
  if (start_byte == end_byte)
    return value >> (8 - (((bin_offset + bin_len) % 8 == 0)
			  ?(8):
			  ((bin_offset + bin_len) % 8)));
  for (unsigned int i = start_byte + 1; i <= end_byte; ++i)
    {
      if (i < end_byte || (bin_offset + bin_len) % 8 == 0)
	value = (value << 8) + _buffer->at(i);
      else
	{
	  //std::cout << "[0] " << (int)_buffer->at(0) << " [1] " << (int)_buffer->at(1) << std::endl;
	  byte = _buffer->at(i) >> (8 - (bin_offset + bin_len) % 8);
	  //std::cout << "byte = " << (int)byte << std::endl;
	  //std::cout << "value << (bin_offset + bin_len) % 8" << (value << (bin_offset + bin_len) % 8) << std::endl;
	  value = (value << (bin_offset + bin_len) % 8) + byte;
	}
    }
  return value;
}

void					Packet::setField(field_t value, unsigned int bin_offset, unsigned int bin_len)
{
  unsigned int		start_byte, end_byte, tmp_val;
  byte_t		save_before, save_after;

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
  //std::cout << "[0] " << (int)_buffer->at(0) << " [1] " << (int)_buffer->at(1) << std::endl;
}

byte_t						*Packet::getStartOfData(unsigned int start_of_data, unsigned int idx) const
{
  unsigned int					i;
  byte_t					*res;
  
  res = &(_buffer->at(start_of_data));
  for (i = 0; i < PACKET_MAXSIZE && idx > 0; ++i)
    if (res[i] == '\0')
      {
	--idx;
	while (res[i + 1] == '\0' && i < PACKET_MAXSIZE)
	  ++i;
      }
  // test if got to idx nth str and that its not pointed to PACKET_MAXSIZE (cuz it would be null)
  if (idx > 0 || i == PACKET_MAXSIZE)
    throw std::runtime_error("getStartOfData(): bad data request");
  return (res + i);
}

byte_t						*Packet::getData(unsigned int start_of_data, unsigned int idx) const
{
  unsigned int					i;
  byte_t					*res;

  res = getStartOfData(start_of_data, idx);
 // test the end of idx nth str has end before maxsize
  for (i = 0; i < PACKET_MAXSIZE && res[i] != '\0'; ++i);
  if (i == PACKET_MAXSIZE)
    throw std::runtime_error ("getData(): bad data request");
  return res;
}

void						Packet::appendData(unsigned int start_of_data, unsigned int idx, byte_t const *value)
{
  byte_t					*res;
  std::size_t					len;
  unsigned int					i, j;

  ///// watch out for BOF ////////////////////////
  len = strnlen((char *)value, PACKET_MAXSIZE);
  ////////////////////////////////////////////////
  if (idx == 0)
    res = &(_buffer->at(start_of_data));
  else
    res = getStartOfData(start_of_data, idx - 1);
  
  // no problem cuz already verified during set
  if (idx > 0)
    {
      for (i = 0; res[i] != '\0'; ++i);
      for (j = 0; value[j] != '\0'; ++j)
	res[i + 1 + j] = value[j];
      res[i + 1 + j] = '\0';    
    }
  else
    {
      for (i = 0; value[i] != '\0'; ++i)
	res[i] = value[i];
      res[i + 1] = '\0';
    }
  _len += len;
}

void		Packet::setDataLen(field_t dataLen)
{
  setField(dataLen, PROTO_DATALEN_OFF, PROTO_DATALEN_SIZE);
}

field_t		Packet::getDataLen() const
{
  return getField(PROTO_DATALEN_OFF, PROTO_DATALEN_SIZE);
}

field_t		Packet::peekDataLen(Packet::buffer_t const &buffer)
{
  return peekField(buffer, PROTO_DATALEN_OFF, PROTO_DATALEN_SIZE);
}

field_t		Packet::peekField(Packet::buffer_t const &buffer, unsigned int bin_offset, unsigned int bin_len)
{
  field_t                               value = 0;
  unsigned int                          start_byte;
  unsigned int                          end_byte;
  byte_t                                byte;

  //  std::cout << "[0] " << (int)_buffer->at(0) << " [1] " << (int)_buffer->at(1) << std::endl;                                                                                                                                             

  start_byte = bin_offset / 8;
  end_byte = (bin_offset + bin_len) / 8;
  if ((bin_offset + bin_len) % 8 == 0)
    --end_byte;

  // byte1              byte2           byte3                                                                                                                                                                                                
  // xxxx.xxBB        BBBB.BBBB         BBxx.xxxx                                                                                                                                                                                            
  // putting only data of start byte beginning at offset;                                                                                                                                                                                    
  byte = buffer.at(start_byte) << (bin_offset % 8);
  byte = byte >> (bin_offset % 8);

  // 0000.00BB -> value;                                                                                                                                                                                                                     

  value = byte;
  //  std::cout << "value = " << value << std::endl;                                                                                                                                                                                         
  if (start_byte == end_byte)
    return value >> (8 - ((bin_offset + bin_len) % 8));
  for (unsigned int i = start_byte + 1; i <= end_byte; ++i)
    {
      if (i < end_byte || (bin_offset + bin_len) % 8 == 0)
        value = (value << 8) + buffer.at(i);
      else
        {
          //std::cout << "[0] " << (int)buffer.at(0) << " [1] " << (int)buffer.at(1) << std::endl;                                                                                                                                       
          byte = buffer.at(i) >> (8 - (bin_offset + bin_len) % 8);
          //std::cout << "byte = " << (int)byte << std::endl;                                                                                                                                                                                
          //std::cout << "value << (bin_offset + bin_len) % 8" << (value << (bin_offset + bin_len) % 8) << std::endl;                                                                                                                        
          value = (value << (bin_offset + bin_len) % 8) + byte;
        }
    }
  return value;
}
