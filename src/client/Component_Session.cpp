#include <Component_Session.h>

Component_Session::Component_Session(IComponent::m_bindings_recv & bindingsRecv, ClientManager *clientManager)
  :IComponent(clientManager), _bindingsRecv(bindingsRecv), _clientManager(clientManager), _logged(false)
{
  BindingsRecv();
  _session = new Session(_clientManager, _clientManager->getIO(), _clientManager->getEndpoint());
}

Component_Session::~Component_Session()
{

}

void	Component_Session::BindingsRecv()
{
  _bindingsRecv[SESSION_AUTH_RESPONSE_OK] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Session::Recv_AuthResponse), SESSION_AUTH_REQUEST);

  _bindingsRecv[SESSION_AUTH_RESPONSE_NOK_BADAUTH] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_AuthResponse), SESSION_AUTH_REQUEST);

  _bindingsRecv[SESSION_AUTH_RESPONSE_NOK_DUPLICATE] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_AuthResponse), SESSION_AUTH_REQUEST);

  _bindingsRecv[SESSION_TIMEOUT] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_TimeOutTest));

  _bindingsRecv[SESSION_KEEPALIVE] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_KeepAlive));

  _bindingsRecv[SESSION_DISCONNECTED] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Disconnected));
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
  if (packet_v1->getType() == SESSION_AUTH_RESPONSE_OK)
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

  _clientManager->Send(static_cast<Packet_v1 *>(packet_v1_SAR), _session, RETRY);
}

void		Component_Session::Send_TimeOutTestRequest()
{
  _clientManager->Send(SESSION_TIMEOUT, _session, NORETRY);
}

void		Component_Session::Send_Disconnect()
{
  _clientManager->Send(SESSION_DISCONNECT, _session, NORETRY);
}

void		Component_Session::Send_KeepAlive()
{
  std::cout << "send_keep_alive" << std::endl;
  _clientManager->Send(SESSION_KEEPALIVE, _session, NORETRY);
}

bool		Component_Session::IsLogged() const
{
  return _logged;
}
