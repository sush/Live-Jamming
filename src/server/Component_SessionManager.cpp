#include <Component_SessionManager.h>

Component_SessionManager::Component_SessionManager(IComponent::m_bindings_recv &bindingsRecv,
						   ServerManager * serverManager)
 :IComponent(serverManager), _bindingsRecv(bindingsRecv), _serverManager(serverManager)
{
  _sessionMap = new m_Session;
  _rng.seed((int32_t)std::clock());
  BindingsRecv();
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
  
  Session	*new_session = new Session(_serverManager, _serverManager->getIO(), packet_v1, GenSessionId());

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


void				Component_SessionManager::Recv_AuthRequest(Packet_v1 const*packet_v1, Session *)
{
  Packet_v1_Session_AuthRequest	const *packet_authRequest =
    static_cast<Packet_v1_Session_AuthRequest const *>(packet_v1);

  packet_authRequest = packet_authRequest;
  std::cout << "packet_auth_request received" << std::endl;
}

void		Component_SessionManager::Send_AuthResponse_OK(Session * session)
{
  _serverManager->Send(SESSION_AUTH_RESPONSE_OK, session, NORETRY);
}

void		Component_SessionManager::Send_AuthResponse_NOK_BADAUTH(Session * session)
{
  _serverManager->Send(SESSION_AUTH_RESPONSE_NOK_BADAUTH, session, NORETRY);
}

void		Component_SessionManager::Send_AuthResponse_NOK_DUPLICATE(Session * session)
{
  _serverManager->Send(SESSION_AUTH_RESPONSE_NOK_DUPLICATE, session, NORETRY);
}


void		Component_SessionManager::Send_KeepAlive(Session *session)
{
  std::cout << "send_keepalive" << std::endl;
  _serverManager->Send(SESSION_KEEPALIVE, session, NORETRY);
}

void		Component_SessionManager::Recv_KeepAlive(Packet_v1 const *, Session *)
{
  std::cout << "packet_keep_alive received" << std::endl;
}

void		Component_SessionManager::Recv_TimeOutTest(Packet_v1 const*, Session *session)
{
  std::cout << "packet_timeout received" << std::endl;
  Send_KeepAlive(session);
}

void		Component_SessionManager::Recv_Disconnect(Packet_v1 const *, Session *)
{
  std::cout << " recv_Disconnected" << std::endl;
}

void		Component_SessionManager::BindingsRecv()
{
  _bindingsRecv[SESSION_AUTH_REQUEST] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_AuthRequest));

  _bindingsRecv[SESSION_KEEPALIVE] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_KeepAlive));

  _bindingsRecv[SESSION_DISCONNECT] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_Disconnect));

  _bindingsRecv[SESSION_TIMEOUT] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_TimeOutTest));
}
