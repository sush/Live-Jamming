#include <Session.h>

 int	_timeOutTest_delay = 10;
 int	_timeOutOccurred_delay = 2;

Session::Session(SessionManager * sessionManager, boost::asio::io_service & io_service, Packet const * packet, unsigned int sessionId)
  :_sessionManager(sessionManager), _io_service(io_service), _sessionId(sessionId)
{
  _ip = packet->getEndpoint().address();
  _port  = packet->getEndpoint().port();
  //  _timer_timeOutTest = new boost::asio::deadline_timer(_io_service, boost::posix_time::seconds(_timeOutTest_delay));
  //  _timer_timeOutOccurred = new boost::asio::deadline_timer(_io_service, boost::posix_time::seconds(_timeOutOccurred_delay));
  _timer_timeOutTest = new boost::asio::deadline_timer(_io_service);
  _timer_timeOutOccurred = new boost::asio::deadline_timer(_io_service);
  setTimeOutTest();
}

Session::~Session()
{
  
}

bool				Session::operator == (Session const & right) const
{
  return (this->_ip == right._ip && this->_port == right._port);
}

bool				Session::operator == (Packet const & right) const
{
  return (this->_ip == right.getEndpoint().address() && this->_port == right.getEndpoint().port());
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

void					Session::setTimeOutTest()
{
  _timer_timeOutTest->cancel();
  _timer_timeOutTest->expires_from_now(boost::posix_time::seconds(_timeOutTest_delay));
  _timer_timeOutTest->async_wait(boost::bind(&SessionManager::CallBack_TimeOutTest, _sessionManager, this, boost::asio::placeholders::error));
}

void					Session::setTimeOutOccurred()
{
  _timer_timeOutOccurred->cancel();
  _timer_timeOutOccurred->expires_from_now(boost::posix_time::seconds(_timeOutOccurred_delay));
  _timer_timeOutOccurred->async_wait(boost::bind(&SessionManager::CallBack_TimeOutOccurred, _sessionManager, this, boost::asio::placeholders::error));
}

void				Session::CancelTimeOutTest()
{
  _timer_timeOutTest->cancel();
}

void				Session::CancelTimeOutOccurred()
{
  _timer_timeOutOccurred->cancel();
}
