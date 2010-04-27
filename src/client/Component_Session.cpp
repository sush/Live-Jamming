#include <Component_Session.h>

Component_Session::Component_Session(IComponent::m_packet_bindings & packetBindings, boost::asio::ip::udp::endpoint & remote_endpoint, boost::asio::ip::udp::socket & socket)
  :_packetBindings(packetBindings), _remote_endpoint(remote_endpoint), _socket(socket)
{
  PacketBindings();
}

Component_Session::~Component_Session()
{

}

void	Component_Session::PacketBindings()
{
  _packetBindings[SESSION_AUTH_RESPOND_OK] =
    {this,static_cast<IComponent::pMethod>(&Component_Session::Recv_AuthResponse_OK)};

  _packetBindings[SESSION_AUTH_RESPOND_NOK_BADAUTH] =
    {this, static_cast<IComponent::pMethod>(&Component_Session::Recv_AuthResponse_NOK)};

  _packetBindings[SESSION_AUTH_RESPOND_NOK_DUPLICATE] =
    {this, static_cast<IComponent::pMethod>(&Component_Session::Recv_AuthResponse_NOK)};

  _packetBindings[SESSION_TIMEOUT] =
    {this, static_cast<IComponent::pMethod>(&Component_Session::Recv_TimeOutTest)};

  _packetBindings[SESSION_KEEPALIVE] =
    {this, static_cast<IComponent::pMethod>(&Component_Session::Recv_KeepAlive)};

  _packetBindings[SESSION_DISCONNECTED] =
    {this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Disconnected)};
}

void		Component_Session::CallBack_handle_send()
{


}

void		Component_Session::Send(Packet_v1 * packet_v1)
{
  _socket.async_send_to(boost::asio::buffer(packet_v1->getData()), _remote_endpoint,
			boost::bind(&Component_Session::CallBack_handle_send, this));
}

void		Component_Session::Connect(std::string const &login, std::string const& pass)
{
  Send_AuthRequest();
}
void		Component_Session::Recv_AuthResponse_OK(Packet_v1 *)
{
  std::cout << "recv_authresponse_ok" << std::endl;
}

void		Component_Session::Recv_AuthResponse_NOK(Packet_v1 *)
{
  std::cout << "recv_authresponse_nok" << std::endl;
}

void		Component_Session::Recv_TimeOutTest(Packet_v1 *)
{
  std::cout << "recv_timeouttest" << std::endl;

}

void		Component_Session::Recv_KeepAlive(Packet_v1 *)
{
  std::cout << "recv_keepalive" << std::endl;

}

void		Component_Session::Recv_Disconnected(Packet_v1 *)
{
  std::cout << "recv_disconnected" << std::endl;

}

void		Component_Session::Send_AuthRequest()
{
  Packet_v1_Session_AuthRequest	*packet_v1_SAR = new Packet_v1_Session_AuthRequest(&_remote_endpoint);
  
  packet_v1_SAR->setLogin("login_not_used_yet");
  packet_v1_SAR->setPass("pass_not_used_yet");

  Send(packet_v1_SAR);
}

void		Component_Session::Send_TimeOutTestRequest()
{
  // send timeOutTestResponse
}

void		Component_Session::Send_Disconnect()
{
  // disconnect
}
