#ifndef __SESSION_H__
#define __SESSION_H__

class Session;

#include <iostream>
#include <boost/asio.hpp>
#include <Packet.h>
#include <SessionManager.h>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

class Session
{
public:
  Session(SessionManager *, boost::asio::io_service &, Packet const *, unsigned int);
  virtual				~Session();
  bool					operator == (Session const &) const;
  bool					operator == (Packet const &) const;

  boost::asio::ip::address		getIP() const;
  unsigned short			getPort() const;
  unsigned int				getSessionId() const;
  void					setTimeOutTest();
  void					setTimeOutOccurred();
  void					CancelTimeOutTest();
  void					CancelTimeOutOccurred();

private:
  SessionManager			*_sessionManager;
  boost::asio::io_service &		_io_service;
  boost::asio::ip::address		_ip;
  unsigned short			_port;
  boost::asio::deadline_timer		*_timer_timeOutTest;
  boost::asio::deadline_timer		*_timer_timeOutOccurred;
  unsigned int				_sessionId;
};




#endif // ! __SESSION_H__
