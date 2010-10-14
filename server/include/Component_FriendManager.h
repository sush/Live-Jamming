#ifndef __COMPONENT_FRIENDMANAGER_H__
#define __COMPONENT_FRIENDMANAGER_H__

class Component_FriendManager;

#include <map>
#include <Server.h>
#include <Packet_v1.h>
#include <Packet_v1_Friend.h>
#include <Session.h>
#include <Protocol.h>
#include <Protocol_Friend.h>
#include <IComponent.h>
#include <ServerManager.h>

class Component_FriendManager :public IComponent
{
  friend class Session;
  friend class ServerManager;

 public:

  Component_FriendManager(ServerManager *);
  virtual			~Component_FriendManager();

 private:

  virtual void			BindingsRecv();
  virtual void			RegisteredRequests();

  void				Connect(Session *session);
  void				Disconnect(Session *);

  void				Send_Friend_Joined(Session *, const char *);
  void				Send_Friend_Leaved(Session *, const char *);

  void				Recv_Friend_Add(Packet_v1 const *, Session *);
  void				Recv_Friend_Del(Packet_v1 const *, Session *);

  void				Send_Friend_Add_OK(Session *, char const *);
  void				Send_Friend_Add_NOK(Session *, char const *);

  void				Send_Friend_Del_OK(Session *, char const *);
  void				Send_Friend_Del_NOK(Session *, char const *);

 private:

  ServerManager			*_serverManager;
  ServerManager::m_Session	&_sessionMap;
};

#endif // ! __COMPONENT_FRIENDMANAGER_H__
