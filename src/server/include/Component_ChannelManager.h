#ifndef __COMPONENT_CHANNEL_H__
#define __COMPONENT_CHANNEL_H__

class Component_Channel;

#include <iostream>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <IComponent.h>
#include <Protocol.h>
#include <Packet_v1.h>
#include <ClientManager.h>

class Component_Channel : public IComponent
{
 public:

  Component_Channel(IComponent::m_packet_bindings &, ClientManager *);
  virtual       ~Component_Channel();
  virtual void  PacketBindings();

 private:

  void          Recv_Channel_MSG(Packet_v1 *);
  void          Recv_Channel_JOIN(Packet_v1 *);
  void          Recv_Channel_LEAVE(Packet_v1 *);

  m_packet_bindings  &                  _packetBindings;
  ClientManager                         *_clientManager;
};

#endif // ! __COMPONENT_CHANNEL_H__
