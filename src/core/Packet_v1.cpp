#include <Packet_v1.h>
#include <Manager.h>
#include <Color.h>

// Packet_v1::Packet_v1(boost::asio::ip::udp::endpoint const *endpoint)
//   : Packet(endpoint)
// {
//   setProtoVersion(PROTOV1);
// }

Packet_v1::Packet_v1(boost::asio::ip::udp::endpoint const *endpoint, buffer_t *buffer, std::size_t len)
  :Packet::Packet(endpoint, buffer, len)
{
  setDataLen(len);
}



Packet_v1::Packet_v1(field_t componentId, field_t requestId)
{
  setProtoVersion(PROTOV1);
  setLen(PROTOV1_START_OF_DATA);
  setComponentId(componentId);
  setRequestId(requestId);
}

Packet_v1::~Packet_v1()
{}

void		Packet_v1::Print(std::string const & componentName, Manager const * manager) const
{
  std::cout << PACKET_STRING << " [Packet_v1] " << PACKET_STRING << std::endl;
  Print_v1(componentName, manager);
  std::cout << PACKET_STRING << PACKET_STRING << PACKET_STRING << std::endl;
}

void		Packet_v1::Print_v1(std::string const & componentName, Manager const * manager) const
{
  Print_base();
  std::cout << "[COMPONENTID: " << componentName << " {" << PROTOV1_COMPONENTID_SIZE << "}]"
	    << "[REQUESTID: ";
  COLOR_REVERSE_START;
  std::cout << manager->getRegisteredRequestName(getComponentId(), getRequestId());
  std::cout << " {" << PROTOV1_REQUESTID_SIZE << "}]"
	    << "[SESSIONID: " << getSessionId() << " {" << PROTOV1_SESSIONID_SIZE << "}]"
	    << "[DATALEN: " << getDataLen() << " {" << PROTOV1_DATALEN_SIZE << "}]"
	    << std::endl;
}

field_t		Packet_v1::peekComponentId(Packet::buffer_t const &buffer)
{
  return peekField(buffer, PROTOV1_COMPONENTID_OFF, PROTOV1_COMPONENTID_SIZE);
}

field_t		Packet_v1::peekRequestId(Packet::buffer_t const &buffer)
{
  return peekField(buffer, PROTOV1_REQUESTID_OFF, PROTOV1_REQUESTID_SIZE);
}

field_t		Packet_v1::peekDataLen(Packet::buffer_t const &buffer)
{
  return peekField(buffer, PROTOV1_DATALEN_OFF, PROTOV1_DATALEN_SIZE);
}

field_t		Packet_v1::peekField(Packet::buffer_t const &buffer, unsigned int bin_offset, unsigned int bin_len)
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


field_t		Packet_v1::getRequestId() const
{
  return getField(PROTOV1_REQUESTID_OFF, PROTOV1_REQUESTID_SIZE);
}

field_t		Packet_v1::getComponentId() const
{
  return getField(PROTOV1_COMPONENTID_OFF, PROTOV1_COMPONENTID_SIZE);
}

field_t		Packet_v1::getSessionId() const
{
  return getField(PROTOV1_SESSIONID_OFF, PROTOV1_SESSIONID_SIZE);
}

field_t		Packet_v1::getDataLen() const
{
  return getField(PROTOV1_DATALEN_OFF, PROTOV1_DATALEN_SIZE);
}

void		Packet_v1::setRequestId(field_t reqId)
{
  setField(reqId, PROTOV1_REQUESTID_OFF, PROTOV1_REQUESTID_SIZE);
}

void		Packet_v1::setComponentId(field_t catId)
{
  setField(catId, PROTOV1_COMPONENTID_OFF, PROTOV1_COMPONENTID_SIZE);
}

void		Packet_v1::setSessionId(field_t sessionId)
{
  setField(sessionId, PROTOV1_SESSIONID_OFF, PROTOV1_SESSIONID_SIZE);
}

void		Packet_v1::setDataLen(field_t dataLen)
{
  setField(dataLen, PROTOV1_DATALEN_OFF, PROTOV1_DATALEN_SIZE);
}
