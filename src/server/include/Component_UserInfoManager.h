#ifndef __COMPONENT_USERINFOMANAGER_H__
#define __COMPONENT_USERINFOMANAGER_H__

#include <map>
#include <IComponent.h>
#include <Protocol.h>
#include <Protocol_UserInfo.h>
#include <Packet_v1.h>
#include <Packet_v1_UserInfo.h>
#include <ServerManager.h>
#include <Session.h>

//! SERVER:  It is used to manage all rooms.

class Component_UserInfoManager : public IComponent
{
  friend class Session;
  friend class ServerManager;

public:

  Component_UserInfoManager(ServerManager *);
  virtual		~Component_UserInfoManager();

private:

  virtual void		BindingsRecv();
  virtual void		RegisteredRequests();

  void			Recv_GetInfo_Request(Packet_v1 const *, Session *);
  void			Recv_GetAvatar_Request(Packet_v1 const *, Session *);

  void			Send_GetInfo_Response_OK(Session *, field_t);
  void			Send_GetInfo_Response_NOK_InvalidUser(Session *, field_t);
  void			Send_GetAvatar_Response_OK(Session *, field_t);
  void			Send_GetAvatar_Response_NOK_InvalidUser(Session *, field_t);

  void			Connect(Session *) {}
  void			Disconnect(Session *) {}

 private :

  ServerManager			*_serverManager;
  ServerManager::m_Session      &_sessionMap;
};

#endif // ! __COMPONENT_USERINFOMANAGER_H__
