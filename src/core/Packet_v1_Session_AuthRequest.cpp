#include <Packet_v1_Session_AuthRequest.h>

Packet_v1_Session_AuthRequest::Packet_v1_Session_AuthRequest(boost::asio::ip::udp::endpoint *endpoint)
  : Packet(endpoint)
{
}

Packet_v1_Session_AuthRequest::~Packet_v1_Session_AuthRequest()
{
}

char const	*Packet_v1_Session_AuthRequest::getLogin() const
{
  
}

char const	*Packet_v1_Session_AuthRequest::getPass() const
{

}

void		Packet_v1_Session_AuthRequest::setLogin(char const *login)
{

}

void		Packet_v1_Session_AuthRequest::setPass(char const *pass)
{

}

