#ifndef __COMPONENT_SESSIONMANAGER_H__
#define __COMPONENT_SESSIONMANAGER_H__

class Component_SessionManager;

#include <iostream>
#include <list>
#include <map>
#include <boost/asio.hpp>
#include <boost/threadpool.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/random.hpp>

#include <Server.h>
#include <Packet_v1.h>
#include <Packet_v1_Session_AuthRequest.h>
#include <Session.h>
#include <Protocol.h>
#include <IComponent.h>

class Component_SessionManager :public IComponent
{
  friend class Session;
  friend class ServerManager;

public:

  Component_SessionManager(IComponent::m_packet_bindings &, boost::asio::io_service &, boost::asio::ip::udp::socket &, boost::threadpool::pool &);
  virtual	~Component_SessionManager();

  void		Manage(Packet *);

private:
  typedef std::list<Session *>			l_Session;
  typedef l_Session::iterator			l_Session_it;
  typedef l_Session::const_iterator		l_Session_cit;

  void					PacketBindings();

  Session				*FindSession(Packet_v1 const *);
  l_Session_it				FindSession_it(Session *);
  Session				*DoAuth(Packet const *);
  bool					IsUniqId(unsigned int) const;
  unsigned int				GenSessionId();
  void					PrintSession(Session const *) const;
  void					PrintSession(Packet const *) const;
  void					Disconnect(Session *);

  void					Recv_AuthRequest(Packet_v1 *);
  void					Recv_Disconnect(Packet_v1 *);
  void					Recv_KeepAlive(Packet_v1 *);
  void					Recv_TimeOutTest(Packet_v1 *);
  void					Send_TimeOutTest(Session *);
  void					Send_AuthResponse();
  void					CallBack_TimeOutTest(Session *, boost::system::error_code const &);
  void					CallBack_TimeOutOccurred(Session *, boost::system::error_code const &);
  

  IComponent::m_packet_bindings		&_packetBindings;
  boost::asio::io_service &		_io_service;
  boost::asio::ip::udp::socket &	_socket;
  boost::threadpool::pool &		_pool;

  boost::rand48				_rng;
  l_Session				*_sessionList;
};

#endif // ! __COMPONENT_SESSIONMANAGER_H__
