#include <Packet_v1.h>

Packet_v1::Packet_v1(boost::asio::ip::udp::endpoint *endpoint)
  : Packet(endpoint)
{

}

Packet_v1::~Packet_v1()
{}

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

