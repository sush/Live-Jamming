#ifndef __COMPONENT_CHANNEL_H__
#define __COMPONENT_CHANNEL_H__

class Component_Channel;

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

  void					Send_Join(Session const *, field_t);
  void					Recv_Join_OK(Packet_v1 const *, Session const *);
  void					Recv_Join_NOK_ALREADYINCHAN(Packet_v1 const *, Session const *);

  void					Recv_Joined(Packet_v1 const *, Session const *);
  void					Send_Joined_ACK(Session const *);

  void					Send_Message(Session const *, std::string const &, field_t);
  void					Recv_Message_RECV(Packet_v1 const *, Session * const);
  void					Send_Message_RECV_ACK(Session const *);

  void					Send_Leave(Session const *, field_t);
  void					Recv_Leave_OK(Packet_v1 const *, Session const *);
  void					Recv_Leave_NOK_NOTINCHAN(Packet_v1 const *, Session const *);
  
  void					Recv_Leaved(Packet_v1 const *, Session const *);
  void					Send_Leaved_ACK(Session const *);
  
  ClientManager				*_clientManager;
  typedef std::map<field_t, Channel *>	m_channel;
  m_channel				_channelMap;
};

#endif
