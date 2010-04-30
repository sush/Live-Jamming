#ifndef __COMPONENT_CHANNELMANAGER_H__
#define __COMPONENT_CHANNELMANAGER_H__

class Component_ChannelManager;

#include <iostream>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <IComponent.h>
#include <Protocol.h>
#include <Packet_v1.h>
#include <ClientManager.h>
#include <boost/thread.hpp>
#include <boost/threadpool.hpp>

class Component_ChannelManager : public IComponent
{
 public:

  Component_ChannelManager(IComponent::m_packet_bindings &, ClientManager *);
  virtual       ~Component_ChannelManager();
  virtual void  PacketBindings();

 private:

  void          Recv_Channel_JOIN(Packet_v1 *);
  void          Recv_Channel_LEAVE(Packet_v1 *);

  m_packet_bindings  &                  _packetBindings;
  ClientManager                         *_clientManager;
  boost::mutex				_channel_mutex;

  typedef std::multimap<std::string, std::vector<int>> m_channel;
  m_channel				_channel;
};

#endif // ! __COMPONENT_CHANNELMANAGER_H__
