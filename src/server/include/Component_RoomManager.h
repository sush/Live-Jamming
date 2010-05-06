#ifndef __COMPONENT_ROOMMANAGER_H__
#define __COMPONENT_ROOMMANAGER_H__

#include <map>
#include <IComponent.h>
#include <Protocol.h>
#include <Packet_v1.h>
#include <ServerManager.h>

class Component_RoomManager : public IComponent
{
public:

  Component_RoomManager(IComponent::m_bindings_recv &, ServerManager *);
  virtual		~Component_RoomManager();
  virtual void		bindingsRecv();

private:

  void          Recv_Joined(Packet_v1 *, Session *);
  void          Recv_Leaved(Packet_v1 *, Session *);
  void          Recv_Kick(Packet_v1 *, Session *);
  void          Recv_Invitation(Packet_v1 *, Session *);
  void          Recv_UpdateSetting(Packet_v1 *, Session *);

  void		Send_Joined_OK(Session *session);
  void		Send_Joined_NOK_ALREADYIN(Session *session);

  void		Send_Leaved_OK(Session *session);
  void		Send_Leaved_NOK_NOTIN(Session *session);

  void		Send_Kick_OK(Session *session);
  void		Send_Kick_NOK_NOTIN(Session *session);

  void		Send_Invitation_OK(Session *session);
  void		Send_Invitation_NOK_ALREADYIN(Session *session);

  // Send update settings ok ??

  Icomponent::m_bindings_recv  &        _bindingsRecv;
  ServerManager                         *_serverManager;
};


#endif // ! __COMPONENT_ROOMMANAGER_H__
