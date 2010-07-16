#include <Packet_v1_Session.h>

Packet_v1_Session::Packet_v1_Session(boost::asio::ip::udp::endpoint const *endpoint, buffer_t *buffer, std::size_t len)
  :Packet_v1::Packet_v1(endpoint, buffer, len)
{}

Packet_v1_Session::Packet_v1_Session(field_t requestId)
  : Packet_v1(SESSION_COMPONENTID, requestId)
{
  std::cout << requestId << std::endl;
  std::cout << "componentId = " << getComponentId() << ", requestId = " << getRequestId() << std::endl;
}

Packet_v1_Session::~Packet_v1_Session()
{}

char const	*Packet_v1_Session::getLogin() const
{
  assert(getRequestId() == SESSION_AUTHREQUEST);
  return reinterpret_cast<char const *>(getData(PROTOV1_SESSION_START_OF_DATA, PROTOV1_SESSION_DATA_LOGIN));
}

char const	*Packet_v1_Session::getPass() const
{
  assert(getRequestId() == SESSION_AUTHREQUEST);
  return reinterpret_cast<char const *>(getData(PROTOV1_SESSION_START_OF_DATA, PROTOV1_SESSION_DATA_PASS));
}

void		Packet_v1_Session::setLogin(char const *login)
{
  assert(getRequestId() == SESSION_AUTHREQUEST);
  appendData(PROTOV1_SESSION_START_OF_DATA, PROTOV1_SESSION_DATA_LOGIN, reinterpret_cast<byte_t const *>(login));
}

void		Packet_v1_Session::setPass(char const *pass)
{
  assert(getRequestId() == SESSION_AUTHREQUEST);
  appendData(PROTOV1_SESSION_START_OF_DATA, PROTOV1_SESSION_DATA_PASS, reinterpret_cast<byte_t const *>(pass));
}

void		Packet_v1_Session::Print(std::string const &componentName, Manager const * manager) const
{
  std::cout << PACKET_STRING << " [Packet_v1_Session] " << PACKET_STRING << std::endl;
  Print_v1_Session(componentName, manager);
  std::cout << PACKET_STRING << PACKET_STRING << PACKET_STRING << std::endl;
}

void		Packet_v1_Session::Print_v1_Session(std::string const &componentName, Manager const * manager) const
{
  Print_v1(componentName, manager);
  if (this->getRequestId() == SESSION_AUTHREQUEST)
    std::cout << "#Login: '" << this->getLogin() << "'" << std::endl
	      << "#Pass: '" << this->getPass() << "'" << std::endl;
}
