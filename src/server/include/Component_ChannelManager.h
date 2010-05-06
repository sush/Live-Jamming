#ifndef __COMPONENT_CHANNELMANAGER_H__
#define __COMPONENT_CHANNELMANAGER_H__

class Component_ChannelManager;

#include <map>
#include <IComponent.h>
#include <Protocol.h>
#include <Packet_v1.h>
#include <ServerManager.h>
#include <Channel.h>

class Component_ChannelManager : public IComponent
{
public:

  Component_ChannelManager(IComponent::m_bindings_recv &, ServerManager *);
  virtual       ~Component_ChannelManager();
  virtual void  bindingsRecv();
  
private:
  
  void          Recv_Join(Packet_v1 *, Session *);
  void          Recv_Leave(Packet_v1 *, Session *);
  void          Recv_Message(Packet_v1 *, Session *);

  void          Send_Joined_OK(Channel *, Packet_v1 *, Session *);
  void          Send_Joined_NOK_ALREADYINCHAN(Session *);

  void          Send_Leave_OK(Channel *, Session *);
  void          Send_Leave_NOK_NOTINCHAN(Session *);

  void          Send_Message(Channel *, Session *, std::string);

  
  Icomponent::m_bindings_recv  &        _bindingsRecv;
  ServerManager                         *_serverManager;
  
  typedef std::map<std::string, Channel*> m_channel;
  m_channel				_channel;
};

#endif // ! __COMPONENT_CHANNELMANAGER_H__
