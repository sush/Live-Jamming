#include <Session.h>

Session::Session(boost::asio::io_service const & io_service, Packet const * packet)
  :_io_service(io_service)
{
  _ip = packet->getEndpoint().getIP();
  _port  = packet->getEndpoint().getPort();
}

Session::~Session()
{
}

bool				Session::operator == (Session const & right) const
{
  return (this->_ip == right->_ip);
}

bool				Session::operator == (Packet const & right) const
{
  return (this->_ip == right.getEndpoint().getIP());
}


boost::asio::ip::address	Session::getIP() const
{
  return _ip;
}

unsigned short			Session::getPort() const
{
  return _port;
}
