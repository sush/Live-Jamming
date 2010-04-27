#include <Packet_v1.h>

Packet_v1::Packet_v1(boost::asio::ip::udp::endpoint *endpoint)
  : Packet(endpoint)
{
  setProtoVersion(PROTOV1);
}

Packet_v1::~Packet_v1()
{}

void		Packet_v1::Print() const
{
  std::cout << "[PROTO_VERSION: " << getProtoVersion() << " {" << PROTO_PROTOVERSION_SIZE << "}]"
	    << "[TYPE: " << getType() << " {" << PROTOV1_TYPE_SIZE << "}]"
	    << "[SESSIONID: " << getSessionId() << " {" << PROTOV1_SESSIONID_SIZE << "}]"
	    << "[DATALEN: " << getDataLen() << " {" << PROTOV1_DATALEN_SIZE << "}]"
	    << std::endl;
}

field_t		Packet_v1::getType() const
{
  return getField(PROTOV1_TYPE_OFF, PROTOV1_TYPE_SIZE);
}

field_t		Packet_v1::getSessionId() const
{
  return getField(PROTOV1_SESSIONID_OFF, PROTOV1_SESSIONID_SIZE);
}

field_t		Packet_v1::getDataLen() const
{
  return getField(PROTOV1_DATALEN_OFF, PROTOV1_DATALEN_SIZE);
}

void		Packet_v1::setType(field_t type)
{
  setField(type, PROTOV1_TYPE_OFF, PROTOV1_TYPE_SIZE);
}

void		Packet_v1::setSessionId(field_t sessionId)
{
  setField(sessionId, PROTOV1_SESSIONID_OFF, PROTOV1_SESSIONID_SIZE);
}

void		Packet_v1::setDataLen(field_t dataLen)
{
  setField(dataLen, PROTOV1_DATALEN_OFF, PROTOV1_DATALEN_SIZE);
}

