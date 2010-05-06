#ifndef __COMPONENT_CHANNEL_H__
#define __COMPONENT_CHANNEL_H__

class Component_Channel;

#include <IComponent.h>
#include <Packet_v1.h>
#include <ClientManager.h>
#include <Session.h>
#include <Packet_v1.h>

class Component_Channel : public IComponent
{
public:

  Component_Channel(IComponent::m_bindings_recv &, ClientManager *);
  virtual		~Component_Channel();
  virtual void		BindingsRecv();

private:

  void			Recv_Message(Packet_v1 *packet_v1);
  void			Recv_Joined(Packet_v1 *packet_v1);
  void			Recv_Leaved(Packet_v1 *packet_v1);

  void			Send_Message(Session *session);
  void			Send_Joined(Session *session);
  void			Send_Leaved(Session *session);

  m_bindings_recv &	_bindingsRecv;
  ClientManager		*_clientManager;


};

#endif
