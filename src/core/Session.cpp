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
  // empty various lists
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

void				Session::setAutoRetry(Packet_v1 * packet_v1)
{
  field_t			componentId = packet_v1->getComponentId(), requestId = packet_v1->getRequestId();
  m_timer			*timerMap;
  boost::asio::deadline_timer	*timer;

  if (_timerMapMap.find(componentId) == _timerMapMap.end())
    _timerMapMap[componentId] = new m_timer;
  timerMap = _timerMapMap.find(componentId)->second;
  
  if (timerMap->find(requestId) == timerMap->end())
    (*timerMap)[requestId] = new boost::asio::deadline_timer(_io_service);
  timer = timerMap->find(requestId)->second;
  timer->expires_from_now(boost::posix_time::seconds(_manager->getRetryDelay()));
  timer->async_wait(boost::bind(&Manager::CallBack_Send_TimeOut, _manager, this, packet_v1, boost::asio::placeholders::error));
}


void				Session::CancelAutoRetry(field_t componentId, field_t requestId)
{
  m_timer			*timerMap;

  if (_timerMapMap.find(componentId) != _timerMapMap.end())
    {
      timerMap = _timerMapMap.find(componentId)->second;
      if (timerMap->find(requestId) != timerMap->end())
	{
	  (*timerMap)[requestId]->cancel();
	  std::cout << "[" << componentId << "] [" << requestId << "] cancelled" << std::endl;
	}
    }
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
