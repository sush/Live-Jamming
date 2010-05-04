#include <Session.h>

Session::Session(Manager * manager, boost::asio::io_service & io_service, Packet_v1 const * packet_v1, unsigned int sessionId)
  :_manager(manager), _io_service(io_service), _sessionId(sessionId), _remote_endpoint(packet_v1->getEndpoint()), _timeOutTestCount(0), _isLogged(true)
{
  _ip = packet_v1->getEndpoint().address();
  _port  = packet_v1->getEndpoint().port();
  
  _timer_timeOutTest = new boost::asio::deadline_timer(_io_service);
  _timer_timeOutOccurred = new boost::asio::deadline_timer(_io_service);
  setTimeOutTest();
}

// session in client when not connected
Session::Session(Manager * manager, boost::asio::io_service & io_service, boost::asio::ip::udp::endpoint &endpoint)
  :_manager(manager), _io_service(io_service), _remote_endpoint(endpoint), _timeOutTestCount(0), _isLogged(false)
{
  _timer_timeOutTest = new boost::asio::deadline_timer(_io_service);
  _timer_timeOutOccurred = new boost::asio::deadline_timer(_io_service);
}

void	Session::Authentificated(Packet_v1 const * packet_v1)
{
  _sessionId = packet_v1->getSessionId();
  _ip = packet_v1->getEndpoint().address();
  _port  = packet_v1->getEndpoint().port();
  setTimeOutTest();
}

Session::~Session()
{
  m_timer_it	it, end = _sendTimerMap.end();
  
  for (it = _sendTimerMap.begin(); it != end; ++it)
    delete it->second;
  delete _timer_timeOutTest;
  delete _timer_timeOutOccurred;
}

bool				Session::operator == (Session const & right) const
{
  return (this->_ip == right._ip && this->_port == right._port &&
	  this->_sessionId == right._sessionId);
}

bool				Session::operator != (Session const & right) const
{
  return ! (*this == right);
}

bool				Session::operator == (Packet_v1 const & right) const
{
  return (this->_ip == right.getEndpoint().address() && this->_port == right.getEndpoint().port() &&
	  this->_sessionId == right.getSessionId());
}

bool				Session::operator != (Packet_v1 const & right) const
{
  return ! (*this == right);
}

boost::asio::ip::address	Session::getIP() const
{
  return _ip;
}

unsigned short			Session::getPort() const
{
  return _port;
}

unsigned int			Session::getSessionId() const
{
  return _sessionId;
}

boost::asio::ip::udp::endpoint const 	&Session::getEndpoint() const
{
  return _remote_endpoint;
}

unsigned int			Session::getTimeOutTestCount() const
{
  return _timeOutTestCount;
}


void					Session::setTimeOutTest()
{
  _timeOutTestCount = 0;
  _timer_timeOutTest->cancel();
  _timer_timeOutTest->expires_from_now(boost::posix_time::seconds(_manager->getTimeOutTestDelay()));
  _timer_timeOutTest->async_wait(boost::bind(&Manager::CallBack_TimeOutTest, _manager, this, boost::asio::placeholders::error));
}

void					Session::setTimeOutOccurred()
{
  _timer_timeOutOccurred->cancel();
  _timer_timeOutOccurred->expires_from_now(boost::posix_time::seconds(_manager->getTimeOutOccurredDelay()));
  _timer_timeOutOccurred->async_wait(boost::bind(&Manager::CallBack_TimeOutOccurred, _manager, this, boost::asio::placeholders::error));
}

void					Session::setTimeOutTestCount(unsigned int count)
{
  _timeOutTestCount = count;
}

void				Session::CancelTimeOutTest()
{
  _timer_timeOutTest->cancel();
}

void				Session::CancelTimeOutOccurred()
{
  _timer_timeOutOccurred->cancel();
}

void				Session::setRetry(Packet_v1 * packet_v1)
{
  proto_v1_packet_type		type = packet_v1->getType();

  if (_sendTimerMap.find(type) == _sendTimerMap.end())
    _sendTimerMap[type] = new boost::asio::deadline_timer(_io_service);
  _sendTimerMap[type]->expires_from_now(boost::posix_time::seconds(_manager->getRetryDelay()));
  _sendTimerMap[type]->async_wait(boost::bind(&Manager::CallBack_Send_TimeOut, _manager, this, packet_v1, boost::asio::placeholders::error));
}


void				Session::CancelTimer(proto_v1_packet_type packetType)
{
  if (_sendTimerMap.find(packetType) != _sendTimerMap.end())
    _sendTimerMap[packetType]->cancel();
  // do we really want to throw an exception in case we try to cancel a non existing timer?
}

bool				Session::IsLogged() const
{
  return _isLogged;
}

void				Session::Print() const
{
  std::cout << "[" << _ip << ":" << _port << "]" << " {" << _sessionId << "}";

}
