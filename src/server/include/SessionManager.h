#ifndef __SESSION_MANAGER_H__
#define __SESSION_MANAGER_H__

class SessionManager;

#include <iostream>
#include <list>
#include <boost/asio.hpp>
#include <boost/threadpool.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/random.hpp>

#include <Server.h>
#include <Packet.h>
#include <Session.h>

#define PROTO_AUTH_REQUEST 1
#define PROTO_AUTH_RESPOND 2

class SessionManager
{
  friend class Session;

public:

  SessionManager(boost::asio::io_service &, boost::threadpool::pool &);
  virtual	~SessionManager();

  void		Manage(Packet *);

private:
  typedef void (SessionManager::*pMethod)();
  struct Packet_binding
  {
    int		type;
    pMethod	method;
  };

  typedef std::list<Session *>		l_Session;
  typedef l_Session::iterator		l_Session_it;
  typedef l_Session::const_iterator	l_Session_cit;

  l_Session_it				FindSession(Packet const *);
  l_Session_it				FindSession(Session *);
  Session				*DoAuth(Packet const *);
  void					TimeOutTest(Session *);
  void					Disconnect(Session *);
  void					CallBack_TimeOutTest(Session *, boost::system::error_code const &);
  void					CallBack_TimeOutOccurred(Session *, boost::system::error_code const &);
  bool					IsUniqId(unsigned int) const;
  unsigned int				GenSessionId();
  void					PrintSession(Session const *) const;
  void					PrintSession(Packet const *) const;
  void					AuthRequest();
  void					AuthRespond();

  boost::rand48				_rng;
  boost::asio::io_service &		_io_service;
  boost::threadpool::pool &		_pool;
  boost::asio::ip::udp::socket *	_socket;
  l_Session				*_sessionList;
  static Packet_binding			Packet_type[];
};



#endif // ! __SESSION_MANAGER_H__
