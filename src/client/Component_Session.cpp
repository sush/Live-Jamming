#include <Component_Session.h>

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
  (*_bindingsRecv)[SESSION_AUTH_RESPONSE_OK] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Session::Recv_AuthResponse));

  (*_bindingsRecv)[SESSION_AUTH_RESPONSE_NOK_BADAUTH] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_AuthResponse));

  (*_bindingsRecv)[SESSION_AUTH_RESPONSE_NOK_DUPLICATE] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_AuthResponse));

  (*_bindingsRecv)[SESSION_TIMEOUT] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_TimeOutTest));

  (*_bindingsRecv)[SESSION_KEEPALIVE] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_KeepAlive));

  (*_bindingsRecv)[SESSION_DISCONNECTED] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Disconnected));
}

void	Component_Session::RegisteredRequests()
{
  // SEND requests
  (*_registeredRequests)[SESSION_AUTH_REQUEST] = 
    new Request(SESSION_AUTH_REQUEST, SEND, "Session Authentification request", RETRY);

  (*_registeredRequests)[SESSION_DISCONNECT] = 
    new Request(SESSION_DISCONNECT, SEND, "Session Disconnect request", NORETRY);

  // RECV requests
  (*_registeredRequests)[SESSION_AUTH_RESPONSE_OK] = 
    new Request(SESSION_AUTH_RESPONSE_OK, RECV, "Session Authentification response OK", SESSION_AUTH_REQUEST);

  (*_registeredRequests)[SESSION_AUTH_RESPONSE_NOK_BADAUTH] = 
    new Request(SESSION_AUTH_RESPONSE_NOK_BADAUTH, RECV, "Session Authentification response Bad Login information", SESSION_AUTH_REQUEST);

  (*_registeredRequests)[SESSION_AUTH_RESPONSE_NOK_DUPLICATE] = 
    new Request(SESSION_AUTH_RESPONSE_NOK_DUPLICATE, RECV, "Session Authentification response Duplicate Login", SESSION_AUTH_REQUEST);

  (*_registeredRequests)[SESSION_DISCONNECTED] = 
    new Request(SESSION_DISCONNECTED, RECV, "Session ended", RESPONSETONOTHING);

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
  if (login == login && pass == pass) // just to stop warnings
    Send_AuthRequest();
}

void		Component_Session::Recv_AuthResponse(Packet_v1 const *packet_v1, Session *session)
{
  if (packet_v1->getRequestId() == SESSION_AUTH_RESPONSE_OK)
    {
      _logged = true;
      session->Authentificated(packet_v1);
      std::cout << "recv_authresponse_ok" << std::endl;
    }
  else
    {}	// auth errors
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

void		Component_Session::Send_AuthRequest()
{
  Packet_v1_Session_AuthRequest	*packet_v1_SAR = new Packet_v1_Session_AuthRequest(&_clientManager->getEndpoint());
  
  packet_v1_SAR->setLogin("login_not_used_yet");
  packet_v1_SAR->setPass("pass_not_used_yet");

  _clientManager->Send(static_cast<Packet_v1 *>(packet_v1_SAR), _session);
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

bool		Component_Session::IsLogged() const
{
  return _logged;
}
