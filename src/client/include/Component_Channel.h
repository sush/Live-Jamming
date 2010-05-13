#ifndef __COMPONENT_CHANNEL_H__
#define __COMPONENT_CHANNEL_H__

class Component_Channel;
#include <iostream>
#include <IComponent.h>
#include <Packet_v1.h>
#include <Packet_v1_Channel.h>
#include <ClientManager.h>
#include <Protocol.h>
#include <Protocol_Channel.h>
#include <Session.h>
#include <Channel.h>

class Component_Channel : public IComponent
{
public:

  Component_Channel(ClientManager *);
  virtual ~Component_Channel();

  virtual void				BindingsRecv();
  virtual void				RegisteredRequests();

private:

  void					Send_Join(Session *, field_t);
  void					Recv_Join_OK(Packet_v1 const *, Session *);
  void					Recv_Join_NOK_ALREADYINCHAN(Packet_v1 const *, Session *);

  void					Recv_Joined(Packet_v1 const *, Session *);
  void					Send_Joined_ACK(Session *);

  void					Send_Message(Session *, char const *, field_t);
  void					Recv_Message_RECV(Packet_v1 const *, Session *);
  void					Send_Message_RECV_ACK(Session *);

  void					Send_Leave(Session *, field_t);
  void					Recv_Leave_OK(Packet_v1 const *, Session *);
  void					Recv_Leave_NOK_NOTINCHAN(Packet_v1 const *, Session *);
  
  void					Recv_Leaved(Packet_v1 const *, Session *);
  void					Send_Leaved_ACK(Session *);
  
  ClientManager				*_clientManager;
  typedef std::map<field_t, Channel *>	m_channel;
  m_channel				_channelMap;
};

#endif
