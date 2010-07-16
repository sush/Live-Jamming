#include <Packet_v1.h>
#include <Manager.h>
#include <Color.h>
#include <Exception.h>

// Packet_v1::Packet_v1(boost::asio::ip::udp::endpoint const *endpoint)
//   : Packet(endpoint)
// {
//   setProtoVersion(PROTOV1);
// }

Packet_v1::Packet_v1(boost::asio::ip::udp::endpoint const *endpoint, buffer_t *buffer, std::size_t len)
  :Packet::Packet(endpoint, buffer, len)
{
  //  if (getLen() != getDataLen())
  //throw(X_MIS_LENGTH);
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

