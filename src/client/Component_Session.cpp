#include <Component_Session.h>

const int		retry_delay = 3;

Component_Session::Component_Session(IComponent::m_packet_bindings & packetBindings, ClientManager *clientManager)
  :IComponent(clientManager), _packetBindings(packetBindings), _clientManager(clientManager), _logged(false), _sessionId(0)
{
  PacketBindings();
  _authRequest_timeout = new boost::asio::deadline_timer(_clientManager->getIO());
}

Component_Session::~Component_Session()
{

}

void	Component_Session::PacketBindings()
{
  _packetBindings[SESSION_AUTH_RESPONSE_OK] =
    {this,static_cast<IComponent::pMethod>(&Component_Session::Recv_AuthResponse)};

  _packetBindings[SESSION_AUTH_RESPONSE_NOK_BADAUTH] =
    {this, static_cast<IComponent::pMethod>(&Component_Session::Recv_AuthResponse)};

  _packetBindings[SESSION_AUTH_RESPONSE_NOK_DUPLICATE] =
    {this, static_cast<IComponent::pMethod>(&Component_Session::Recv_AuthResponse)};

  _packetBindings[SESSION_TIMEOUT] =
    {this, static_cast<IComponent::pMethod>(&Component_Session::Recv_TimeOutTest)};

  _packetBindings[SESSION_KEEPALIVE] =
    {this, static_cast<IComponent::pMethod>(&Component_Session::Recv_KeepAlive)};

  _packetBindings[SESSION_DISCONNECTED] =
    {this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Disconnected)};
}

field_t		Component_Session::getSessionId() const
{
  return _sessionId;
}

ClientManager	&Component_Session::getClientManager()
{
  return *_clientManager;
}

void		Component_Session::Connect(std::string const &login, std::string const& pass)
{
  Send_AuthRequest();
}

void		Component_Session::Recv_AuthResponse(Packet_v1 *packet_v1)
{
  _sessionId = packet_v1->getSessionId();
  _authRequest_timeout->cancel();
  std::cout << "recv_authresponse_ok" << std::endl;
}

void		Component_Session::Recv_TimeOutTest(Packet_v1 *)
{
  Send_KeepAlive();
}

void		Component_Session::Recv_KeepAlive(Packet_v1 *)
{
  std::cout << "recv_keepalive" << std::endl;

}

void		Component_Session::Recv_Disconnected(Packet_v1 *)
{
  _logged = false;
  std::cout << "recv_disconnected" << std::endl;

}

void		Component_Session::CallBack_AuthRequest_timeout(boost::system::error_code const & error_code)
{
  if (error_code != boost::asio::error::operation_aborted)
    {
      std::cout << "AuthRequest timed out! resending..." << std::endl;
      Send_AuthRequest();
    }
}

void		Component_Session::Send_AuthRequest()
{
  Packet_v1_Session_AuthRequest	*packet_v1_SAR = new Packet_v1_Session_AuthRequest(&_clientManager->getEndpoint());
  
  packet_v1_SAR->setLogin("login_not_used_yet");
  packet_v1_SAR->setPass("pass_not_used_yet");

  _clientManager->Send(packet_v1_SAR);
  _authRequest_timeout->expires_from_now(boost::posix_time::seconds(retry_delay));
  _authRequest_timeout->async_wait(boost::bind(&Component_Session::CallBack_AuthRequest_timeout, this, boost::asio::placeholders::error));
}

void		Component_Session::Send_TimeOutTestRequest()
{
  _clientManager->Send(SESSION_TIMEOUT);
}

void		Component_Session::Send_Disconnect()
{
  _clientManager->Send(SESSION_DISCONNECT);
}

void		Component_Session::Send_KeepAlive()
{
  _clientManager->Send(SESSION_KEEPALIVE);
}

bool		Component_Session::IsLogged() const
{
  return _logged;
}
