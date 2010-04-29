#include <Component_SessionManager.h>

Component_SessionManager::Component_SessionManager(IComponent::m_packet_bindings &packetBindings,
						   ServerManager * serverManager)
  :IComponent(serverManager), _packetBindings(packetBindings), _serverManager(serverManager)
{
  _sessionMap = new m_Session;
  _rng.seed(std::clock());
  PacketBindings();
}

Component_SessionManager::~Component_SessionManager()
{}

unsigned int		Component_SessionManager::GenSessionId()
{
  unsigned int	sessionId;

  do {
    sessionId = _rng();
  } while (! IsUniqId(sessionId));
  return sessionId;
}

bool		Component_SessionManager::IsUniqId(unsigned int sessionId) const
{
  return (_sessionMap->find(sessionId) == _sessionMap->end());
}

void		Component_SessionManager::PrintSession(Session const * session) const
{
  std::cout << "[" << session->getIP() << ":" << session->getPort() << "]" <<
    "{" << session->getSessionId() << "}";

}

void		Component_SessionManager::PrintSession(Packet const * packet) const
{
  std::cout << "[" << packet->getEndpoint().address() << ":" << packet->getEndpoint().port() << "]" <<
    "{}";
}

Session		*Component_SessionManager::FindSession(Packet_v1 const * packet_v1)
{
  m_Session_it	it;
  Session	*session;

  it = _sessionMap->find(packet_v1->getSessionId());
  session = it->second;
  if (it == _sessionMap->end() || *session != *packet_v1)
    return 0;
  return it->second;
}

unsigned int	Component_SessionManager::CountActiveSessions() const
{
  return _sessionMap->size();
}

Session 	*Component_SessionManager::DoAuth(Packet_v1 const * packet_v1)
{
  // if packet is auth request type
  // extract auth information from
  
  Session	*new_session = new Session(this, _serverManager->getIO(), packet_v1, GenSessionId());

  (*_sessionMap)[new_session->getSessionId()] = new_session;
  Send_AuthResponse_OK(new_session);
  return new_session;
}

void		Component_SessionManager::Disconnect(Session * session)
{
  PrintSession(session);
  std::cout << " Disconnected" << std::endl;
  _sessionMap->erase(session->getSessionId());
}

void		Component_SessionManager::Send_TimeOutTest(Session * session)
{
  _serverManager->Send(SESSION_TIMEOUT, session);
  PrintSession(session);
  std::cout << "-> sending timeout test" << std::endl;
  session->CancelTimeOutTest();
  session->setTimeOutOccurred();
}

void		Component_SessionManager::CallBack_TimeOutTest(Session * session, boost::system::error_code const & error_code)
{
  if (error_code != boost::asio::error::operation_aborted)
      _serverManager->getPool().schedule(boost::bind(&Component_SessionManager::Send_TimeOutTest, this, session));
}

void		Component_SessionManager::CallBack_TimeOutOccurred(Session * session, boost::system::error_code const & error_code)
{
  if (error_code != boost::asio::error::operation_aborted)
    _serverManager->getPool().schedule(boost::bind(&Component_SessionManager::Disconnect, this, session));
}

void				Component_SessionManager::Recv_AuthRequest(Packet_v1 *packet_v1)
{
  Packet_v1_Session_AuthRequest	*packet_authRequest =
    static_cast<Packet_v1_Session_AuthRequest *>(packet_v1);

  std::cout << "packet_auth_request received" << std::endl;
}

void		Component_SessionManager::Send_AuthResponse_OK(Session * session)
{
  _serverManager->Send(SESSION_AUTH_RESPONSE_OK, session);
}

void		Component_SessionManager::Send_AuthResponse_NOK_BADAUTH(Session * session)
{
  _serverManager->Send(SESSION_AUTH_RESPONSE_NOK_BADAUTH, session);
}

void		Component_SessionManager::Send_AuthResponse_NOK_DUPLICATE(Session * session)
{
  _serverManager->Send(SESSION_AUTH_RESPONSE_NOK_DUPLICATE, session);
}


void		Component_SessionManager::Send_KeepAlive(Session *session)
{
  _serverManager->Send(SESSION_KEEPALIVE, session);
}

void		Component_SessionManager::Recv_KeepAlive(Packet_v1 *)
{
  std::cout << "packet_keep_alive received" << std::endl;
}

void		Component_SessionManager::Recv_TimeOutTest(Packet_v1 *)
{
  std::cout << "packet_timeout received" << std::endl;
}

void		Component_SessionManager::Recv_Disconnect(Packet_v1 * packet_v1)
{
  std::cout << " recv_Disconnected" << std::endl;
}

void		Component_SessionManager::PacketBindings()
{
  _packetBindings[SESSION_AUTH_REQUEST] =
    {this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_AuthRequest)};
  _packetBindings[SESSION_KEEPALIVE] =
    {this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_KeepAlive)};
  _packetBindings[SESSION_DISCONNECT] =
    {this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_Disconnect)};
  _packetBindings[SESSION_TIMEOUT] =
    {this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_TimeOutTest)};
}
