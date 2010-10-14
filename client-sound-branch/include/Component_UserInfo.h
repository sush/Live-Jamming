#ifndef __COMPONENT_USERINFO_H__
#define __COMPONENT_USERINFO_H__

#include <map>
#include <ClientManager.h>
#include <IComponent.h>
#include <Protocol.h>
#include <Protocol_UserInfo.h>
#include <Packet_v1.h>
#include <Packet_v1_UserInfo.h>
#include <Session.h>

//! SERVER:  It is used to manage all rooms.

class Component_UserInfo : public IComponent
{
public:

  Component_UserInfo(ClientManager *);
  virtual		~Component_UserInfo();

private:

  virtual void		BindingsRecv();
  virtual void		RegisteredRequests();

  void			Recv_GetInfo_Response_OK(Packet_v1 const *, Session *);
  void			Recv_GetInfo_Response_NOK_InvalidUser(Packet_v1 const *, Session *);
  void			Recv_GetAvatar_Response_OK(Packet_v1 const *, Session *);
  void			Recv_GetAvatar_Response_NOK_InvalidUser(Packet_v1 const *, Session *);

  void			Send_GetInfo_Request(Session *, field_t);
  void			Send_GetAvatar_Request(Session *, field_t);

  void			Connect(Session *) {}
  void			Disconnect(Session *) {}

 private :

  ClientManager			*_clientManager;
  ClientManager::m_user	        &_userMap;
  ClientManager::m_avatar	&_avatarMap;
};

#endif // ! __COMPONENT_USERINFO_H__
