#ifndef __COMPONENT_CHANNELMANAGER_H__
#define __COMPONENT_CHANNELMANAGER_H__

class Component_ChannelManager;

#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
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
  
  void          Recv_JOIN(Packet_v1 *, Session *);
  void          Recv_LEAVE(Packet_v1 *, Session *);
  void          Recv_MSG(Packet_v1 *, Session *);

  void          Send_JOINED_OK(Channel *, Packet_v1 *, Session *);
  void          Send_JOINED_NOK_ALREADYINCHAN(Session *);
  void          Send_LEAVED_OK(Channel *, Session *);
  void          Send_LEAVED_NOK_NOTINCHAN(Session *);
  void          Send_MSG(Channel *, Session *, std::string);

  
  Icomponent::m_bindings_recv  &        _bindingsRecv;
  ServerManager                         *_serverManager;
  
  typedef std::map<std::string, Channel*> m_channel;
  m_channel				_channel;
};

#endif // ! __COMPONENT_CHANNELMANAGER_H__
