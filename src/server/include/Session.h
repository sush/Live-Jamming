#ifndef __SESSION_H__
#define __SESSION_H__

class Session;

#include <iostream>
#include <boost/asio.hpp>
#include <Packet_v1.h>
#include <Component_SessionManager.h>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

class Session
{
public:
  Session(Component_SessionManager *, boost::asio::io_service &, Packet_v1 const *, unsigned int);
  virtual				~Session();
  bool					operator == (Session const &) const;
  bool					operator != (Session const &) const;
  bool					operator == (Packet_v1 const &) const;
  bool					operator != (Packet_v1 const &) const;

  boost::asio::ip::udp::endpoint const &	getEndpoint() const;
  boost::asio::ip::address			getIP() const;
  unsigned short				getPort() const;
  field_t					getSessionId() const;
  void						setTimeOutTest();
  void						setTimeOutOccurred();
  void						CancelTimeOutTest();
  void						CancelTimeOutOccurred();

private:
  Component_SessionManager		*_sessionManager;
  boost::asio::io_service &		_io_service;
  boost::asio::ip::address		_ip;
  unsigned short			_port;
  boost::asio::deadline_timer		*_timer_timeOutTest;
  boost::asio::deadline_timer		*_timer_timeOutOccurred;
  unsigned int				_sessionId;
  boost::asio::ip::udp::endpoint const	&_remote_endpoint;
};




#endif // ! __SESSION_H__
