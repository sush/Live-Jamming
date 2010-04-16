#ifndef __SESSION_MANAGER_H__
#define __SESSION_MANAGER_H__

class SessionManager;

#include <iostream>
#include <boost/asio.hpp>

#include <Packet.h>
#include <Session.h>
#include <list>
#include <Server.h>

class SessionManager
{
public:

  SessionManager(boost::asio::io_service const &);
  virtual	~SessionManager();

  void		Manage(Packet *);



private:
  typedef std::list<Session *>		l_Session;
  typedef l_Session::iterator		l_Session_it;
  typedef l_Session::const_iterator	l_Session_cit;

  Session 				* FindSession(Packet const *) const;
  Session				*DoAuth(Packet const *);
  void					Disconnect(Session const *);

  boost::asio::ip::udp::socket *	_socket;
  boost::asio::io_service const &	_io_service;
  l_Session				_sessionList;
};



#endif // ! __SESSION_MANAGER_H__
