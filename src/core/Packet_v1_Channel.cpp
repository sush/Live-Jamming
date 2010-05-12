#include <Packet_v1_Channel.h>

Packet_v1::Packet_v1(boost::asio::ip::udp::endpoint const *endpoint)
  : Packet(endpoint)
{
  setProtoVersion(PROTOV1);
}

Packet_v1::~Packet_v1()
{}

void		Packet_v1::Print() const
{
  // problem with dynamic_cast from Packet* to Packet_v1*
  // wrong function is called so Print_v1 was created
  Print_v1();  
}

void		Packet_v1::Print_v1() const
{
  std::cout << "[PROTO_VERSION: " << getProtoVersion() << " {" << PROTO_PROTOVERSION_SIZE << "}]"
	    << "[COMPONENTID: " << getComponentId() << " {" << PROTOV1_COMPONENTID_SIZE << "}]"
	    << "[REQUESTID: " << getRequestId() << " {" << PROTOV1_REQUESTID_SIZE << "}]"
	    << "[SESSIONID: " << getSessionId() << " {" << PROTOV1_SESSIONID_SIZE << "}]"
	    << "[DATALEN: " << getDataLen() << " {" << PROTOV1_DATALEN_SIZE << "}]"
	    << std::endl;
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

char		*Packet_v1::getStartOfData()
{
  return (char *)_buffer->at(PROTOV1_START_OF_DATA);
}
