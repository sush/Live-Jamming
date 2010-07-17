#ifndef __COMPONENT_SESSIONMANAGER_H__
#define __COMPONENT_SESSIONMANAGER_H__

class Component_SessionManager;
class Session;
class UserModule_mysql;
class Packet_v1;
class Packet;
class Packet_v1_Session;
class ServerManager;

#include <iostream>
#include <list>
#include <map>
#include <boost/asio.hpp>
#include <boost/threadpool.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/random.hpp>

#include <IComponent.h>
#include <ServerManager.h>

class Component_SessionManager :public IComponent
{
  friend class Session;
  friend class ServerManager;

public:

  Component_SessionManager(ServerManager *);
  virtual				~Component_SessionManager();
  
  void					Manage(Packet *);
  UserModule_mysql			*getUserModule();

private:
  virtual void				BindingsRecv();
  virtual void				RegisteredRequests();

  Session				*FindSession(Packet_v1 const *);
  unsigned int				CountActiveSessions() const;
  Session				*DoAuth(Packet_v1_Session const *);
  bool					IsUniqId(unsigned int) const;
  unsigned int				GenSessionId();
  void					PrintSession(Session const *) const;
  void					PrintSession(Packet const *) const;

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

  void                                  Connect(Session *);
  void                                  Disconnect(Session *);

 private:

  ServerManager				*_serverManager;
  boost::rand48				_rng;
  ServerManager::m_Session		&_sessionMap;
  UserModule_mysql			*_userModule;
};

#endif // ! __COMPONENT_SESSIONMANAGER_H__
