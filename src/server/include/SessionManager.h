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
#include <Packet_v1.h>
#include <Session.h>
#include <Protocol.h>

class SessionManager
{
  friend class Session;

public:

  SessionManager(boost::asio::io_service &, boost::threadpool::pool &);
  virtual	~SessionManager();

  void		Manage(Packet *);

private:
  typedef void (SessionManager::*pMethod)(Packet_v1 *);
  struct Packet_binding
  {
    proto_v1_packet_type		type;
    pMethod				method;
  };

  typedef std::list<Session *>		l_Session;
  typedef l_Session::iterator		l_Session_it;
  typedef l_Session::const_iterator	l_Session_cit;

  l_Session_it				FindSession(Packet_v1 const *);
  l_Session_it				FindSession(Session *);
  Session				*DoAuth(Packet const *);
  void					TimeOutTest(Session *);
  void					CallBack_TimeOutTest(Session *, boost::system::error_code const &);
  void					CallBack_TimeOutOccurred(Session *, boost::system::error_code const &);
  bool					IsUniqId(unsigned int) const;
  unsigned int				GenSessionId();
  void					PrintSession(Session const *) const;
  void					PrintSession(Packet const *) const;
  void					Disconnect(Session *);
  void					Packet_AuthRequest(Packet_v1 *);
  void					Packet_Disconnect(Packet_v1 *);
  void					Packet_KeepAlive(Packet_v1 *);
  void					Packet_TimeOut(Packet_v1 *);
  void					AuthRespond();

  boost::rand48				_rng;
  boost::asio::io_service &		_io_service;
  boost::threadpool::pool &		_pool;
  boost::asio::ip::udp::socket *	_socket;
  l_Session				*_sessionList;
  static Packet_binding			Packet_type[];
};



#endif // ! __SESSION_MANAGER_H__
