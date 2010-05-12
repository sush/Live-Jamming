#ifndef __COMPONENT_CHANNELMANAGER_H__
#define __COMPONENT_CHANNELMANAGER_H__

class Component_ChannelManager;

#include <map>
#include <IComponent.h>
#include <Protocol.h>
#include <Protocol_Channel.h>
#include <Packet_v1.h>
#include <Packet_v1_Channel.h>
#include <ServerManager.h>
#include <Channel.h>
#include <Session.h>

class Component_ChannelManager : public IComponent
{
  friend class Session;
  friend class ServerManager;

public:

  Component_ChannelManager(ServerManager *);
  virtual       ~Component_ChannelManager();

  virtual void  bindingsRecv();
  virtual void	RegisteredRequests();
  
private:
  
  void          Recv_Join(Packet_v1 *, Session const *);
  void          Send_Join_OK(Session const *, field_t);
  void          Send_Join_NOK_ALREADYINCHAN(Session const *, field_t);

  void		Send_Joined(Session const *, field_t, field_t);

  void          Recv_Message(Packet_v1 const *, Session const *);
  void		Send_Message_ACK(Session const *);
  void		Send_Message_RECV(Session const *, std::string const &, field_t);

  void          Recv_Leave(Packet_v1 const *, Session const *);
  void          Send_Leave_OK(Session const *, field_t);
  void          Send_Leave_NOK_NOTINCHAN(Session const *, field_t);

  void		Send_Leaved(Session const *, field_t, field_t);

  ServerManager                         *_serverManager;
  typedef std::map<field_t, Channel*>	m_channel;
  m_channel				_channelMap;
};

#endif // ! __COMPONENT_CHANNELMANAGER_H__
