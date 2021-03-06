#include <Session.h>

#include <Packet_v1.h>
#include <Manager.h>
#include <Protocol_Session.h>

Session::Session(Manager * manager, boost::asio::io_service & io_service, Packet_v1 const * packet_v1, unsigned int sessionId)
  :_manager(manager), _io_service(io_service), _sessionId(sessionId), _remote_endpoint(packet_v1->getEndpoint()), _timeOutTestCount(0), _isLogged(true)
{
  _userinfo = 0;
  _avatar = 0;
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
  _userinfo = 0;
  _avatar = 0;
  _timer_timeOutTest = new boost::asio::deadline_timer(_io_service);
  _timer_timeOutOccurred = new boost::asio::deadline_timer(_io_service);
}

void	Session::Authentificated(Packet_v1 const * packet_v1)
{
  _isLogged = true;
  _sessionId = packet_v1->getSessionId();
  _ip = packet_v1->getEndpoint().address();
  _port  = packet_v1->getEndpoint().port();
  setTimeOutTest();
}

void	Session::DeAuthentificated()
{
  _isLogged = false;
  CancelTimeOutTest();
  CancelTimeOutOccurred();
  _timerMapMap.clear();
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
  PacketTimer			*packetTimer;

  if (_timerMapMap.find(componentId) == _timerMapMap.end())
    _timerMapMap[componentId] = new m_timer;
  timerMap = _timerMapMap.find(componentId)->second;
  
  if (timerMap->find(requestId) == timerMap->end())
    (*timerMap)[requestId] = new PacketTimer(this, _manager, _io_service);
  packetTimer = timerMap->find(requestId)->second;
  packetTimer->setAutoRetry(packet_v1);
}


// void				Session::CancelAll()
// {
//   m_m_timer_it			it1, end1 = _timerMapMap.end();
//   m_timer_it			it2, end2;

//   for (it1 = _timerMapMap.begin(); it1 != end1; ++it1)
//     {
//       end2 = it1->second->end();
//       for (it2 = it1->second->begin(); it2 != end2; ++it2)
// 	it2->second
//     }

// }

void				Session::CancelAutoRetry(field_t componentId, field_t requestId)
{
  m_timer			*timerMap;

  if (_timerMapMap.find(componentId) != _timerMapMap.end())
    {
      timerMap = _timerMapMap.find(componentId)->second;
      if (timerMap->find(requestId) != timerMap->end())
	{
	  (*timerMap)[requestId]->CancelAutoRetry();
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

void				Session::setLogin(std::string const &login)
{
  _login = login;
}

std::string const &		Session::getLogin() const
{
  return _login;
}

Session::l_Friend 		&Session::getFriendList()
{
  return _friendList;
}

void				Session::setFriendList(Session::l_Friend &friendList)
{
  _friendList = friendList;
}

Packet_v1 const *			Session::getOriginatedPacket(field_t componentId, field_t requestId) const
{
  m_timer			*timerMap;
  PacketTimer			*packetTimer;

  std::cout << "getOriginatedPacket() componentId = " << componentId << ", requestId = " << requestId << std::endl;
  if (_timerMapMap.find(componentId) == _timerMapMap.end())
    {
      assert(1);
      return 0;
    }
  timerMap = _timerMapMap.find(componentId)->second;
  
  if (timerMap->find(requestId) == timerMap->end())
    {
      assert(1);
      return 0;
    }
  packetTimer = timerMap->find(requestId)->second;
  return packetTimer->getPacket();
}

/////////////////////////////////// Session::PacketTimer ///////////////////////////////

Session::PacketTimer::PacketTimer(Session * session, Manager * manager, boost::asio::io_service & io_service)
  :_session(session), _manager(manager), _packet_v1(0)
{
  _timer = new boost::asio::deadline_timer(io_service);
}

Session::PacketTimer::~PacketTimer()
{
  delete _timer;
  delete _packet_v1;
}

void	Session::PacketTimer::setAutoRetry(Packet_v1 *packet_v1)
{
  if (_packet_v1 &&
      packet_v1 != _packet_v1)
    //delete _packet_v1;
    ;
  _packet_v1 = packet_v1;
  _timer->expires_from_now(boost::posix_time::seconds(_manager->getRetryDelay()));
  _timer->async_wait(boost::bind(&Manager::CallBack_Send_TimeOut, _manager, _session, _packet_v1, boost::asio::placeholders::error));
}

void	Session::PacketTimer::CancelAutoRetry()
{
  _timer->cancel();
  //  delete _packet_v1;
  _packet_v1 = 0;
}

Packet_v1	*Session::PacketTimer::getPacket()
{
  return _packet_v1;
}

m_userinfo const	*Session::getUserInfo() const
{
  return _userinfo;
}

char const		*Session::getAvatar() const
{
  return _avatar;
}

void			Session::setUserInfo(m_userinfo const * userinfo)
{
  _userinfo = userinfo;
}

void			Session::setAvatar(char const * avatar)
{
  _avatar = avatar;
}
