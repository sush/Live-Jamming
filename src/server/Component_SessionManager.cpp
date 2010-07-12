#include <Component_SessionManager.h>
#include <Bind_recv.h>

Component_SessionManager::Component_SessionManager(ServerManager * serverManager)
  :IComponent(SESSION_COMPONENTID), _serverManager(serverManager)
{
  _sessionMap = new m_Session;
  _rng.seed((int32_t)std::clock());
  _userModule_mysql = UserModule_mysql::getInstance();
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

Session 	*Component_SessionManager::DoAuth(Packet_v1_Session const * packet_v1_Session)
{
  Session	*new_session;
  assert(packet_v1_Session->getRequestId() == SESSION_AUTHREQUEST);

  char const *login = packet_v1_Session->getLogin();
  char const *pass = packet_v1_Session->getPass();
  
  // THIS HAS TO BE OPTIMIZED
  // convert to string remove
  std::string login_str(login);
  std::string pass_str(pass);
  ///////////////////////////

  std::cout << "packet_auth_request received" << std::endl;
  std::cout << "login = [" << login << "] pass = " << pass << std::endl;
  if (_userModule_mysql->Authentification(login_str, pass_str))
    {
      field_t			sessionId	= GenSessionId();
      std::vector<std::string> const friendList	= _userModule_mysql->getFriendList(login_str);

      new_session = new Session(_serverManager, _serverManager->getIO(), packet_v1_Session, sessionId);
      new_session->setLogin(login_str);
      new_session->setFriendList(friendList);

      (*_sessionMap)[new_session->getSessionId()] = new_session;
      Send_AuthResponse_OK(new_session);

      m_Session::iterator it, end = _sessionMap->end();
      for (it = _sessionMap->begin(); it != end; ++it)
	{
	  for (unsigned int i = 0; i < friendList.size(); ++i)
	    {
	      if (it->second->getLogin() == friendList[i])
		{
		  Send_Friend_Joined(new_session, it->second->getLogin().c_str());
		  Send_Friend_Joined(it->second, login_str.c_str());
		}
	    }
	}

      std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< AUTH OK >>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    }
  else 
    {
      _serverManager->Send(_componentId, SESSION_AUTHRESPONSE_NOK_BADAUTH, packet_v1_Session->getEndpoint());
      std::cout << "!!!!!!!!!!!!!!!!!!!!!!! AUTH NOK !!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    }
  return new_session;
}

void		Component_SessionManager::Disconnect(Session * session)
{
  PrintSession(session);
  std::cout << " Disconnected" << std::endl;

  m_Session::iterator it, end		= _sessionMap->end();
  std::vector<std::string> friendList	= session->getFriendList();

  for (it = _sessionMap->begin(); it != end; ++it)
    {
      for (unsigned int i = 0; i < friendList.size(); ++i)
	{
	  if (it->second->getLogin() == friendList[i])
	    Send_Friend_Leaved(it->second, session->getLogin().c_str());
	}
    }
  _sessionMap->erase(session->getSessionId());
}


void				Component_SessionManager::Recv_AuthRequest(Packet_v1 const*packet_v1, Session *)
{
  Packet_v1_Session	const *packet_v1_Session =
    static_cast<Packet_v1_Session const *>(packet_v1);

  DoAuth(packet_v1_Session);
}

void		Component_SessionManager::Send_AuthResponse_OK(Session * session)
{
  _serverManager->Send(_componentId, SESSION_AUTHRESPONSE_OK, session);
}

void		Component_SessionManager::Send_AuthResponse_NOK_BADAUTH(Session * session)
{
  _serverManager->Send(_componentId, SESSION_AUTHRESPONSE_NOK_BADAUTH, session);
}

void		Component_SessionManager::Send_AuthResponse_NOK_DUPLICATE(Session * session)
{
  _serverManager->Send(_componentId, SESSION_AUTHRESPONSE_NOK_DUPLICATE, session);
}


void		Component_SessionManager::Send_KeepAlive(Session *session)
{
  std::cout << "send_keepalive" << std::endl;
  _serverManager->Send(_componentId, SESSION_KEEPALIVE, session);
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

void		Component_SessionManager::Recv_Disconnect(Packet_v1 const *, Session * session)
{
  _serverManager->Disconnect(session);
}

void		Component_SessionManager::Send_Friend_Joined(Session *session, const char *clientLogin)
{
  Packet_v1_Session *packet_v1_session = new Packet_v1_Session(SESSION_FRIEND_JOINED);

  packet_v1_session->setFriendLogin(clientLogin);
  _serverManager->Send(packet_v1_session, session);
}

void		Component_SessionManager::Send_Friend_Leaved(Session *session, const char *clientLogin)
{
  Packet_v1_Session *packet_v1_session = new Packet_v1_Session(SESSION_FRIEND_LEAVED);

  packet_v1_session->setFriendLogin(clientLogin);
  _serverManager->Send(packet_v1_session, session);
}

void		Component_SessionManager::Recv_Add_Friend(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Session	const *packet_v1_session =
    static_cast<Packet_v1_Session const *>(packet_v1);

  char const * friendLogin = packet_v1_session->getFriendLogin();
  // call userModule->AddFriend(session->getLogin(), friendLogin);
  // if ok 
  // Send_Add_Friend_OK(session, friendLogin);
  // else
  // Send_Add_Friend_NOK(session, friendLogin);
}

void		Component_SessionManager::Recv_Del_Friend(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Session	const *packet_v1_session =
    static_cast<Packet_v1_Session const *>(packet_v1);

  char const * friendLogin = packet_v1_session->getFriendLogin();
  // call userModule->DelFriend(session->getLogin(), friendLogin);
  // if ok 
  // Send_Del_Friend_OK(session, friendLogin);
  // else
  // Send_Del_Friend_NOK(session, friendLogin);
}

void		Component_SessionManager::Send_Add_Friend_OK(Session *session, char const *friendLogin)
{
  Packet_v1_Session *packet_v1_session = new Packet_v1_Session(SESSION_ADD_FRIEND_OK);

  packet_v1_session->setFriendLogin(friendLogin);
  _serverManager->Send(packet_v1_session, session);
}

void		Component_SessionManager::Send_Add_Friend_NOK(Session *session, char const *friendLogin)
{
  Packet_v1_Session *packet_v1_session = new Packet_v1_Session(SESSION_ADD_FRIEND_NOK);

  packet_v1_session->setFriendLogin(friendLogin);
  _serverManager->Send(packet_v1_session, session);
}

void		Component_SessionManager::Send_Del_Friend_OK(Session *session, char const *friendLogin)
{
  Packet_v1_Session *packet_v1_session = new Packet_v1_Session(SESSION_DEL_FRIEND_OK);

  packet_v1_session->setFriendLogin(friendLogin);
  _serverManager->Send(packet_v1_session, session);
}

void		Component_SessionManager::Send_Del_Friend_NOK(Session *session, char const *friendLogin)
{
  Packet_v1_Session *packet_v1_session = new Packet_v1_Session(SESSION_DEL_FRIEND_NOK);

  packet_v1_session->setFriendLogin(friendLogin);
  _serverManager->Send(packet_v1_session, session);
}

void		Component_SessionManager::BindingsRecv()
{
  (*_bindingsRecv)[SESSION_AUTHREQUEST] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_AuthRequest));

  (*_bindingsRecv)[SESSION_KEEPALIVE] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_KeepAlive));

  (*_bindingsRecv)[SESSION_DISCONNECT] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_Disconnect));

  (*_bindingsRecv)[SESSION_TIMEOUT] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_TimeOutTest));

  (*_bindingsRecv)[SESSION_ADD_FRIEND] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_Add_Friend));

  (*_bindingsRecv)[SESSION_DEL_FRIEND] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_Del_Friend));
}


void	Component_SessionManager::RegisteredRequests()
{
  // SEND requests 
  (*_registeredRequests)[SESSION_AUTHRESPONSE_OK] = 
    new Request(SESSION_AUTHRESPONSE_OK, SEND, "Session Authentification response OK", NORETRY);

  (*_registeredRequests)[SESSION_AUTHRESPONSE_NOK_BADAUTH] = 
    new Request(SESSION_AUTHRESPONSE_NOK_BADAUTH, SEND, "Session Authentification response Bad Login information", NORETRY);

  (*_registeredRequests)[SESSION_AUTHRESPONSE_NOK_DUPLICATE] = 
    new Request(SESSION_AUTHRESPONSE_NOK_DUPLICATE, SEND, "Session Authentification response Duplicate Login", NORETRY);

  (*_registeredRequests)[SESSION_FRIEND_JOINED] = 
    new Request(SESSION_FRIEND_JOINED, SEND, "Session friend joined notification", NORETRY);

  (*_registeredRequests)[SESSION_FRIEND_LEAVED] = 
    new Request(SESSION_FRIEND_LEAVED, SEND, "Session friend leaved notification", NORETRY);

  (*_registeredRequests)[SESSION_ADD_FRIEND_OK] = 
    new Request(SESSION_ADD_FRIEND_OK, SEND, "Session friend add OK notification", NORETRY);

  (*_registeredRequests)[SESSION_ADD_FRIEND_NOK] = 
    new Request(SESSION_ADD_FRIEND_NOK, SEND, "Session friend add NOK notification", NORETRY);

  (*_registeredRequests)[SESSION_DEL_FRIEND_OK] = 
    new Request(SESSION_DEL_FRIEND_OK, SEND, "Session friend del OK notification", NORETRY);

  (*_registeredRequests)[SESSION_DEL_FRIEND_NOK] = 
    new Request(SESSION_DEL_FRIEND_NOK, SEND, "Session friend del NOK notification", NORETRY);
  
  // RECV requests
  (*_registeredRequests)[SESSION_AUTHREQUEST] = 
    new Request(SESSION_AUTHREQUEST, RECV, "Session Authentification request", RESPONSETONOTHING);

  (*_registeredRequests)[SESSION_DISCONNECT] = 
    new Request(SESSION_DISCONNECT, RECV, "Session Disconnect request", RESPONSETONOTHING);

  (*_registeredRequests)[SESSION_DISCONNECTED] = 
    new Request(SESSION_DISCONNECTED, RECV, "Session ended", RESPONSETONOTHING);

  (*_registeredRequests)[SESSION_ADD_FRIEND] = 
    new Request(SESSION_ADD_FRIEND, RECV, "Add friend request", RESPONSETONOTHING);

  (*_registeredRequests)[SESSION_DEL_FRIEND] = 
    new Request(SESSION_DEL_FRIEND, RECV, "Del friend request", RESPONSETONOTHING);

  // BIDIRECTIONNAL requests 
  (*_registeredRequests)[SESSION_TIMEOUT] = 
    new Request(SESSION_TIMEOUT, BIDIRECTIONNAL, "Session timeout request", NORETRY, RESPONSETONOTHING);

  (*_registeredRequests)[SESSION_KEEPALIVE] =   // keepalive is a response actually but its managed on its own
    new Request(SESSION_TIMEOUT, BIDIRECTIONNAL, "Session keepalive response", NORETRY, RESPONSETONOTHING);
}
