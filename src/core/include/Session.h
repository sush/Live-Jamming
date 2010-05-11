#ifndef __SESSION_H__
#define __SESSION_H__

class Session;

#include <iostream>
#include <map>
#include <boost/asio.hpp>
#include <Packet_v1.h>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <Protocol.h>
#include <Manager.h>
#include <Protocol_Session.h>

class Session
{
public:
  // [SERVER] session for client in server once connected
		Session(Manager *, boost::asio::io_service &, Packet_v1 const *, unsigned int);

  // [CLIENT] session in client when not connected
  Session(Manager * manager, boost::asio::io_service &, boost::asio::ip::udp::endpoint &);
  
  void		Authentificated(Packet_v1 const *);

  virtual				~Session();
  bool					operator == (Session const &) const;
  bool					operator != (Session const &) const;
  bool					operator == (Packet_v1 const &) const;
  bool					operator != (Packet_v1 const &) const;
  
  boost::asio::ip::udp::endpoint const		&getEndpoint() const;
  boost::asio::ip::address			getIP() const;
  unsigned short				getPort() const;
  field_t					getSessionId() const;
  bool						IsLogged() const;
  void						Print() const;

  unsigned int					getTimeOutTestCount() const;
  void						setTimeOutTest();
  void						setTimeOutOccurred();
  void						setTimeOutTestCount(unsigned int);

  void						CancelTimeOutTest();
  void						CancelTimeOutOccurred();
  void						setAutoRetry(Packet_v1 *);
  void						CancelAutoRetry(field_t, field_t);

private:
  typedef std::map<field_t, boost::asio::deadline_timer *>		m_timer;
  typedef m_timer::iterator						m_timer_it;
  typedef m_timer::const_iterator					m_timer_cit;
  typedef std::map<field_t, m_timer *>					m_m_timer;
  typedef m_m_timer::iterator						m_m_timer_it;
  typedef m_m_timer::const_iterator					m_m_timer_cit;
  
  Manager				*_manager;
  boost::asio::io_service &		_io_service;
  boost::asio::ip::address		_ip;
  unsigned short			_port;
  boost::asio::deadline_timer		*_timer_timeOutTest;
  boost::asio::deadline_timer		*_timer_timeOutOccurred;
  unsigned int				_sessionId;
  boost::asio::ip::udp::endpoint const	&_remote_endpoint;
  unsigned int				_timeOutTestCount;
  m_m_timer				_timerMapMap;
  bool					_isLogged;
};

#endif // ! __SESSION_H__
