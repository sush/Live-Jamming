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
#include <ServerManager.h>

class Component_SessionManager :public IComponent
{
  friend class Session;
  friend class ServerManager;

public:

  Component_SessionManager(IComponent::m_packet_bindings &, ServerManager *);
  virtual	~Component_SessionManager();

  void		Manage(Packet *);

private:
  typedef std::map<field_t, Session *>			m_Session;
  typedef m_Session::iterator				m_Session_it;
  typedef m_Session::const_iterator			m_Session_cit;

  void					PacketBindings();

  Session				*FindSession(Packet_v1 const *);
  Session				*DoAuth(Packet_v1 const *);
  bool					IsUniqId(unsigned int) const;
  unsigned int				GenSessionId();
  void					PrintSession(Session const *) const;
  void					PrintSession(Packet const *) const;
  void					Disconnect(Session *);

  //recv
  void					Recv_AuthRequest(Packet_v1 *);
  void					Recv_Disconnect(Packet_v1 *);
  void					Recv_KeepAlive(Packet_v1 *);
  void					Recv_TimeOutTest(Packet_v1 *);
  // send
  void					Send_TimeOutTest(Session *);
  void					Send_AuthResponse_OK(Session *);
  void					Send_AuthResponse_NOK_BADAUTH(Session *);
  void					Send_AuthResponse_NOK_DUPLICATE(Session *);
  void					Send_KeepAlive(Session *);

  void					CallBack_TimeOutTest(Session *, boost::system::error_code const &);
  void					CallBack_TimeOutOccurred(Session *, boost::system::error_code const &);
  

  IComponent::m_packet_bindings		&_packetBindings;
  ServerManager				*_serverManager;

  boost::rand48				_rng;
  m_Session				*_sessionMap;
};

#endif // ! __COMPONENT_SESSIONMANAGER_H__
