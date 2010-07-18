#include <Component_SessionManager.h>
#include <Bind_recv.h>

#include <Server.h>
#include <Packet_v1.h>
#include <Packet_v1_Session.h>
#include <Session.h>
#include <Protocol.h>
#include <Protocol_Session.h>
#include <UserModule_mysql.h>

Component_SessionManager::Component_SessionManager(ServerManager * serverManager)
  :IComponent(SESSION_COMPONENTID), _serverManager(serverManager), _sessionMap(serverManager->getSessionMap())
{
  _rng.seed((int32_t)std::clock());
  _userModule = UserModule_mysql::getInstance();
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
  return (_sessionMap.find(sessionId) == _sessionMap.end());
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

Session				*Component_SessionManager::FindSession(Packet_v1 const * packet_v1)
{
  ServerManager::m_Session_it	it;
  Session			*session;

  it = _sessionMap.find(packet_v1->getSessionId());
  session = it->second;
  if (it == _sessionMap.end() || *session != *packet_v1)
    return 0;
  return it->second;
}

unsigned int	Component_SessionManager::CountActiveSessions() const
{
  return _sessionMap.size();
}

Session				*Component_SessionManager::DoAuth(Packet_v1_Session const * packet_v1_Session)
{
  Session			*new_session;
  m_userinfo const		*userinfo;

  assert(packet_v1_Session->getRequestId() == SESSION_AUTHREQUEST);

  char const *login = packet_v1_Session->getLogin();
  char const *pass = packet_v1_Session->getPass();
  
  // THIS HAS TO BE OPTIMIZED
  // convert to string remove
  std::string login_str(login);
  std::string pass_str(pass);
  ///////////////////////////

  if (userinfo = _userModule->Authentification(login_str, pass_str))
    {
      field_t			sessionId	= GenSessionId();
      //std::vector<std::string> const friendList	= _userModule->getFriendList(login_str);
      
      new_session = new Session(_serverManager, _serverManager->getIO(), packet_v1_Session, sessionId);
      new_session->setLogin(login_str);
      new_session->setUserInfo(userinfo);
      //      new_session->setFriendList(friendList);
      
      _sessionMap[new_session->getSessionId()] = new_session;
      Send_AuthResponse_OK(new_session);
      _serverManager->Connect(new_session);
      // m_Session::iterator it, end = _sessionMap.end();
      // for (it = _sessionMap.begin(); it != end; ++it)
      // 	{
      // 	  for (unsigned int i = 0; i < friendList.size(); ++i)
      // 	    {
      // 	      if (it->second->getLogin() == friendList[i])
      // 		{
      // 		  Send_Friend_Joined(new_session, it->second->getLogin().c_str());
      // 		  Send_Friend_Joined(it->second, login_str.c_str());
      // 		}
      // 	    }
      // 	}
      // Send_Friend_List(new_session, friendList);
    }
  else 
    _serverManager->Send(_componentId, SESSION_AUTHRESPONSE_NOK_BADAUTH, packet_v1_Session->getEndpoint());
  return new_session;
}

void		Component_SessionManager::Disconnect(Session * session)
{
  session->DeAuthentificated();
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
  _serverManager->Send(_componentId, SESSION_KEEPALIVE, session);
}

void		Component_SessionManager::Recv_KeepAlive(Packet_v1 const *, Session *)
{
}

void		Component_SessionManager::Recv_TimeOutTest(Packet_v1 const*, Session *session)
{
  Send_KeepAlive(session);
}

void		Component_SessionManager::Recv_Disconnect(Packet_v1 const *, Session * session)
{
  _serverManager->Disconnect(session);
}

UserModule_mysql *Component_SessionManager::getUserModule()
{
  return _userModule;
}

void		Component_SessionManager::Connect(Session *)
{}

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
}

void	Component_SessionManager::RegisteredRequests()
{
  // SEND requests 
  (*_registeredRequests)[SESSION_AUTHRESPONSE_OK] = 
    new Request(SESSION_AUTHRESPONSE_OK, SEND, "AUTHRESPONSE_OK", NORETRY);

  (*_registeredRequests)[SESSION_AUTHRESPONSE_NOK_BADAUTH] = 
    new Request(SESSION_AUTHRESPONSE_NOK_BADAUTH, SEND, "AUTHRESPONSE_NOK_BADAUTH", NORETRY);

  (*_registeredRequests)[SESSION_AUTHRESPONSE_NOK_DUPLICATE] = 
    new Request(SESSION_AUTHRESPONSE_NOK_DUPLICATE, SEND, "AUTHRESPONSE_NOK_DUPLICATE", NORETRY);
 
  // RECV requests
  (*_registeredRequests)[SESSION_AUTHREQUEST] = 
    new Request(SESSION_AUTHREQUEST, RECV, "AUTHREQUEST", RESPONSETONOTHING);

  (*_registeredRequests)[SESSION_DISCONNECT] = 
    new Request(SESSION_DISCONNECT, RECV, "DISCONNECT", RESPONSETONOTHING);

  (*_registeredRequests)[SESSION_DISCONNECTED] = 
    new Request(SESSION_DISCONNECTED, RECV, "DISCONNECTED", RESPONSETONOTHING);
  // BIDIRECTIONNAL requests 
  (*_registeredRequests)[SESSION_TIMEOUT] = 
    new Request(SESSION_TIMEOUT, BIDIRECTIONNAL, "TIMEOUT_TEST", NORETRY, RESPONSETONOTHING);

  (*_registeredRequests)[SESSION_KEEPALIVE] =   // keepalive is a response actually but its managed on its own
    new Request(SESSION_TIMEOUT, BIDIRECTIONNAL, "KEEPALIVE", NORETRY, RESPONSETONOTHING);
}
