#include <Component_Session.h>
#include <Bind_recv.h>
#include <proxy.h>

Component_Session::Component_Session(ClientManager *clientManager)
  :IComponent(SESSION_COMPONENTID), _clientManager(clientManager), _logged(false), _session(0)
{
  _session = new Session(_clientManager, _clientManager->getIO(), _clientManager->getEndpoint());
}

Component_Session::~Component_Session()
{}

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
}

void	Component_Session::RegisteredRequests()
{
  // SEND requests
  (*_registeredRequests)[SESSION_AUTHREQUEST] = 
    new Request(SESSION_AUTHREQUEST, SEND, "AUTHREQUEST", RETRY);

  (*_registeredRequests)[SESSION_DISCONNECT] = 
    new Request(SESSION_DISCONNECT, SEND, "DISCONNECT", NORETRY);

  // RECV requests
  (*_registeredRequests)[SESSION_AUTHRESPONSE_OK] = 
    new Request(SESSION_AUTHRESPONSE_OK, RECV, "AUTHRESPONSE_OK", SESSION_AUTHREQUEST);

  (*_registeredRequests)[SESSION_AUTHRESPONSE_NOK_BADAUTH] = 
    new Request(SESSION_AUTHRESPONSE_NOK_BADAUTH, RECV, "AUTHRESPONSE_NOK_BADAUTH", SESSION_AUTHREQUEST);

  (*_registeredRequests)[SESSION_AUTHRESPONSE_NOK_DUPLICATE] = 
    new Request(SESSION_AUTHRESPONSE_NOK_DUPLICATE, RECV, "AUTHRESPONSE_NOK_DUPLICATE", SESSION_AUTHREQUEST);

  (*_registeredRequests)[SESSION_DISCONNECTED] = 
    new Request(SESSION_DISCONNECTED, RECV, "DISCONNECTED", RESPONSETONOTHING);

  // BIDIRECTIONAL requests 
  (*_registeredRequests)[SESSION_TIMEOUT] = 
    new Request(SESSION_TIMEOUT, BIDIRECTIONNAL, "TIMEOUT_TEST", NORETRY, RESPONSETONOTHING);

  (*_registeredRequests)[SESSION_KEEPALIVE] =   // keepalive is a response actually but its managed on its own
    new Request(SESSION_TIMEOUT, BIDIRECTIONNAL, "KEEPALIVE", NORETRY, RESPONSETONOTHING);
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
  Send_AuthRequest(login, pass);
}

void		Component_Session::Recv_AuthResponse(Packet_v1 const *packet_v1, Session *session)
{
  if (packet_v1->getRequestId() == SESSION_AUTHRESPONSE_OK)
    {
      _logged = true;
      session->Authentificated(packet_v1);
    }
  else
    {}	// auth errors
}

void		Component_Session::Disconnect()
{
  _logged = false;
  Send_Disconnect();
  _session->DeAuthentificated();
}

void		Component_Session::Recv_TimeOutTest(Packet_v1 const *, Session *)
{
  Send_KeepAlive();
}

void		Component_Session::Recv_KeepAlive(Packet_v1 const *, Session *)
{
}

void		Component_Session::Recv_Disconnected(Packet_v1 const *, Session *)
{
  _logged = false;
}

void		Component_Session::Send_AuthRequest(std::string const &login, std::string const &pass)
{
  Packet_v1_Session	*packet_v1_Session = new Packet_v1_Session(SESSION_AUTHREQUEST);
  
  _session->setLogin(login);
  packet_v1_Session->setLogin(login.c_str());
  packet_v1_Session->setPass(pass.c_str());
  
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
  _clientManager->Send(_componentId, SESSION_KEEPALIVE, _session);
}

bool		Component_Session::IsLogged() const
{
  return _logged;
}

void		Component_Session::Connect(Session *)
{
}
