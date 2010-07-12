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
#include <Packet_v1_Session.h>
#include <Session.h>
#include <Protocol.h>
#include <Protocol_Session.h>
#include <IComponent.h>
#include <ServerManager.h>
#include <UserModule_mysql.h>

class Component_SessionManager :public IComponent
{
  friend class Session;
  friend class ServerManager;

public:

  Component_SessionManager(ServerManager *);
  virtual	~Component_SessionManager();
  
  void		Manage(Packet *);

private:
  typedef std::map<field_t, Session *>			m_Session;
  typedef m_Session::iterator				m_Session_it;
  typedef m_Session::const_iterator			m_Session_cit;

  virtual void					BindingsRecv();
  virtual void					RegisteredRequests();

  Session				*FindSession(Packet_v1 const *);
  unsigned int				CountActiveSessions() const;
  Session				*DoAuth(Packet_v1_Session const *);
  bool					IsUniqId(unsigned int) const;
  unsigned int				GenSessionId();
  void					PrintSession(Session const *) const;
  void					PrintSession(Packet const *) const;
  void					Disconnect(Session *);

  //recv
  void					Recv_AuthRequest(Packet_v1 const *, Session *);
  void					Recv_Disconnect(Packet_v1 const *, Session *);
  void					Recv_KeepAlive(Packet_v1 const *, Session *);
  void					Recv_TimeOutTest(Packet_v1 const *, Session *);
  // send
  void					Send_AuthResponse_OK(Session *);
  void					Send_AuthResponse_NOK_BADAUTH(Session *);
  void					Send_AuthResponse_NOK_DUPLICATE(Session *);
  void					Send_KeepAlive(Session *);

  void					Send_Friend_Joined(Session *, const char *);
  void					Send_Friend_Leaved(Session *, const char *);

  void		Recv_Add_Friend(Packet_v1 const *, Session *);
  void		Recv_Del_Friend(Packet_v1 const *, Session *);

  void		Send_Add_Friend_OK(Session *, char const *);
  void		Send_Add_Friend_NOK(Session *, char const *);

  void		Send_Del_Friend_OK(Session *, char const *);
  void		Send_Del_Friend_NOK(Session *, char const *);

  ServerManager				*_serverManager;

  boost::rand48				_rng;
  m_Session				*_sessionMap;
  UserModule_mysql			*_userModule_mysql;
};

#endif // ! __COMPONENT_SESSIONMANAGER_H__
