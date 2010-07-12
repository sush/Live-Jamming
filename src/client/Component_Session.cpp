#include <Component_Session.h>
#include <Bind_recv.h>
#include <proxy.h>

Component_Session::Component_Session(ClientManager *clientManager)
  :IComponent(SESSION_COMPONENTID), _clientManager(clientManager), _logged(false), _session(0)
{
  _session = new Session(_clientManager, _clientManager->getIO(), _clientManager->getEndpoint());
}

Component_Session::~Component_Session()
{

}

void	Component_Session::BindingsRecv()
{
  (*_bindingsRecv)[SESSION_AUTHRESPONSE_OK] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_AuthResponse),
                  static_cast<Proxy*>(_clientManager), static_cast<Proxy::pMethod>(&Proxy::authResponse));

  (*_bindingsRecv)[SESSION_AUTHRESPONSE_NOK_BADAUTH] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_AuthResponse),
                  static_cast<Proxy*>(_clientManager), static_cast<Proxy::pMethod>(&Proxy::authResponse));

  (*_bindingsRecv)[SESSION_AUTHRESPONSE_NOK_DUPLICATE] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_AuthResponse),
                  static_cast<Proxy*>(_clientManager), static_cast<Proxy::pMethod>(&Proxy::authResponse));

  (*_bindingsRecv)[SESSION_TIMEOUT] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_TimeOutTest));

  (*_bindingsRecv)[SESSION_KEEPALIVE] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_KeepAlive));

  (*_bindingsRecv)[SESSION_DISCONNECTED] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Disconnected));

  (*_bindingsRecv)[SESSION_FRIEND_JOINED] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Friend_Leaved));

  (*_bindingsRecv)[SESSION_FRIEND_LEAVED] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Friend_Joined));

  (*_bindingsRecv)[SESSION_ADD_FRIEND_OK] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Add_Friend_OK));

  (*_bindingsRecv)[SESSION_ADD_FRIEND_NOK] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Add_Friend_NOK));

  (*_bindingsRecv)[SESSION_DEL_FRIEND_OK] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Del_Friend_OK));

  (*_bindingsRecv)[SESSION_DEL_FRIEND_NOK] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Del_Friend_NOK));

}

void	Component_Session::RegisteredRequests()
{
  // SEND requests
  (*_registeredRequests)[SESSION_AUTHREQUEST] = 
    new Request(SESSION_AUTHREQUEST, SEND, "Session Authentification request", RETRY);

  (*_registeredRequests)[SESSION_DISCONNECT] = 
    new Request(SESSION_DISCONNECT, SEND, "Session Disconnect request", NORETRY);

  (*_registeredRequests)[SESSION_ADD_FRIEND] = 
    new Request(SESSION_ADD_FRIEND, SEND, "Add friend request", RETRY);

  (*_registeredRequests)[SESSION_DEL_FRIEND] = 
    new Request(SESSION_DEL_FRIEND, SEND, "Del friend request", RETRY);

  // RECV requests
  (*_registeredRequests)[SESSION_AUTHRESPONSE_OK] = 
    new Request(SESSION_AUTHRESPONSE_OK, RECV, "Session Authentification response OK", SESSION_AUTHREQUEST);

  (*_registeredRequests)[SESSION_AUTHRESPONSE_NOK_BADAUTH] = 
    new Request(SESSION_AUTHRESPONSE_NOK_BADAUTH, RECV, "Session Authentification response Bad Login information", SESSION_AUTHREQUEST);

  (*_registeredRequests)[SESSION_AUTHRESPONSE_NOK_DUPLICATE] = 
    new Request(SESSION_AUTHRESPONSE_NOK_DUPLICATE, RECV, "Session Authentification response Duplicate Login", SESSION_AUTHREQUEST);

  (*_registeredRequests)[SESSION_DISCONNECTED] = 
    new Request(SESSION_DISCONNECTED, RECV, "Session ended", RESPONSETONOTHING);

  (*_registeredRequests)[SESSION_FRIEND_LEAVED] = 
    new Request(SESSION_FRIEND_LEAVED, RECV, "Friend leaved", RESPONSETONOTHING);

  (*_registeredRequests)[SESSION_FRIEND_JOINED] = 
    new Request(SESSION_FRIEND_JOINED, RECV, "Friend Joined", RESPONSETONOTHING);

  (*_registeredRequests)[SESSION_ADD_FRIEND_OK] = 
    new Request(SESSION_ADD_FRIEND_OK, RECV, "Friend add request OK", SESSION_ADD_FRIEND);

  (*_registeredRequests)[SESSION_ADD_FRIEND_NOK] = 
    new Request(SESSION_ADD_FRIEND_NOK, RECV, "Friend add request NOK", SESSION_ADD_FRIEND);

  (*_registeredRequests)[SESSION_DEL_FRIEND_OK] = 
    new Request(SESSION_DEL_FRIEND_OK, RECV, "Friend del request OK", SESSION_DEL_FRIEND);

  (*_registeredRequests)[SESSION_DEL_FRIEND_NOK] = 
    new Request(SESSION_DEL_FRIEND_NOK, RECV, "Friend del request NOK", SESSION_DEL_FRIEND);

  // BIDIRECTIONAL requests 
  (*_registeredRequests)[SESSION_TIMEOUT] = 
    new Request(SESSION_TIMEOUT, BIDIRECTIONNAL, "Session timeout request", NORETRY, RESPONSETONOTHING);

  (*_registeredRequests)[SESSION_KEEPALIVE] =   // keepalive is a response actually but its managed on its own
    new Request(SESSION_TIMEOUT, BIDIRECTIONNAL, "Session keepalive response", NORETRY, RESPONSETONOTHING);
}

field_t		Component_Session::getSessionId() const
{
  if (!_session)
    return 0;
  return _session->getSessionId();
}

ClientManager	&Component_Session::getClientManager()
{
  return *_clientManager;
}

Session		*Component_Session::getSession()
{
  return _session;
}

void		Component_Session::Connect(std::string const &login, std::string const& pass)
{
  for (unsigned int i = 0; i < login.size() + 1; ++i)
    std::cout << "[" << i << "] " << login.c_str()[i] << std::endl;
  Send_AuthRequest(login, pass);
}

void		Component_Session::Recv_AuthResponse(Packet_v1 const *packet_v1, Session *session)
{
  if (packet_v1->getRequestId() == SESSION_AUTHRESPONSE_OK)
    {
      _logged = true;
      session->Authentificated(packet_v1);
      std::cout << "recv_authresponse_ok" << std::endl;
    }
  else
    {std::cout << "auth failed" << std::endl;}	// auth errors
}

void		Component_Session::Disconnect()
{
  _logged = false;
  std::cout << "disconnecting..." << std::endl;
  Send_Disconnect();
}

void		Component_Session::Recv_TimeOutTest(Packet_v1 const *, Session *)
{
  std::cout << "recv_timeouttest" << std::endl;
  Send_KeepAlive();
}

void		Component_Session::Recv_KeepAlive(Packet_v1 const *, Session *)
{
  std::cout << "recv_keepalive" << std::endl;

}

void		Component_Session::Recv_Disconnected(Packet_v1 const *, Session *)
{
  _logged = false;
  std::cout << "recv_disconnected" << std::endl;

}

void		Component_Session::Send_AuthRequest(std::string const &login, std::string const &pass)
{
  Packet_v1_Session	*packet_v1_Session = new Packet_v1_Session(SESSION_AUTHREQUEST);
  
  _session->setLogin(login);
  std::cout << "login = " << login.c_str() << std::endl;
  packet_v1_Session->setLogin(login.c_str());
  packet_v1_Session->setPass(pass.c_str());
  
  std::cout << "login = " << packet_v1_Session->getLogin() << std::endl;
  std::cout << "pass = " << packet_v1_Session->getPass() << std::endl;

  _clientManager->Send(packet_v1_Session, _session);
}

void		Component_Session::Send_TimeOutTestRequest()
{
  _clientManager->Send(_componentId, SESSION_TIMEOUT, _session);
}

void		Component_Session::Send_Disconnect()
{
  _clientManager->Send(_componentId, SESSION_DISCONNECT, _session);
}

void		Component_Session::Send_KeepAlive()
{
  std::cout << "send_keep_alive" << std::endl;
  _clientManager->Send(_componentId, SESSION_KEEPALIVE, _session);
}

void		Component_Session::Recv_Friend_Joined(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Session const *packet_v1_session =
    static_cast<Packet_v1_Session const *>(packet_v1);

  char const *friendLogin = packet_v1_session->getFriendLogin();

  std::cout << "FRIEND [" << friendLogin << "] has JOINED the application" << std::endl;
}

void		Component_Session::Recv_Friend_Leaved(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Session const *packet_v1_session =
    static_cast<Packet_v1_Session const *>(packet_v1);

  char const *friendLogin = packet_v1_session->getFriendLogin();

  std::cout << "FRIEND [" << friendLogin << "] has LEAVED the application" << std::endl;
}

void		Component_Session::Send_Add_Friend(char const *friendLogin)
{
  Packet_v1_Session	*packet_v1_session = new Packet_v1_Session(SESSION_ADD_FRIEND);

  packet_v1_session->setFriendLogin(friendLogin);

  std::cout << "SEND ADD FRIEND [" << friendLogin << "] " << std::endl;

  _clientManager->Send(packet_v1_session, _session);
}

void		Component_Session::Send_Del_Friend(char const *friendLogin)
{
  Packet_v1_Session	*packet_v1_session = new Packet_v1_Session(SESSION_DEL_FRIEND);

  packet_v1_session->setFriendLogin(friendLogin);

  std::cout << "SEND DEL FRIEND [" << friendLogin << "] " << std::endl;

  _clientManager->Send(packet_v1_session, _session);
}

void		Component_Session::Recv_Add_Friend_OK(Packet_v1 const *packet_v1, Session *session)
{
 Packet_v1_Session const *packet_v1_session =
    static_cast<Packet_v1_Session const *>(packet_v1);

  char const *friendLogin = packet_v1_session->getFriendLogin();

  std::cout << "FRIEND [" << friendLogin << "] has been ADDED" << std::endl;
}

void		Component_Session::Recv_Add_Friend_NOK(Packet_v1 const *packet_v1, Session *session)
{
 Packet_v1_Session const *packet_v1_session =
    static_cast<Packet_v1_Session const *>(packet_v1);

  char const *friendLogin = packet_v1_session->getFriendLogin();

  std::cout << "FRIEND [" << friendLogin << "] has NOT been ADDED" << std::endl;
}

void		Component_Session::Recv_Del_Friend_OK(Packet_v1 const *packet_v1, Session *session)
{
 Packet_v1_Session const *packet_v1_session =
    static_cast<Packet_v1_Session const *>(packet_v1);

  char const *friendLogin = packet_v1_session->getFriendLogin();

  std::cout << "FRIEND [" << friendLogin << "] has been DELETED" << std::endl;
}

void		Component_Session::Recv_Del_Friend_NOK(Packet_v1 const *packet_v1, Session *session)
{
 Packet_v1_Session const *packet_v1_session =
    static_cast<Packet_v1_Session const *>(packet_v1);

  char const *friendLogin = packet_v1_session->getFriendLogin();

  std::cout << "FRIEND [" << friendLogin << "] has NOT been DELETED" << std::endl;
}

bool		Component_Session::IsLogged() const
{
  return _logged;
}
