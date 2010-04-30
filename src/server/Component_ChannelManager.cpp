#include <Component_ChannelManager.h>

Component_ChannelManager::Component_ChannelManager(IComponent::m_packet_bindings & packetBindings, ClientManager *clientManager) 
 :IComponent(clientManager), _packetBindings(packetBindings), _clientManager(clientManager) 
{
  PacketBindings();
}

void	Component_ChannelManager::PacketBindings() 
{
  _packetBindings[CHANNEL_JOIN] =
    {this,static_cast<IComponent::pMethod>(&Component_ChannelManager::Recv_Channel_JOIN)};

  _packetBindings[CHANNEL_LEAVE] =
    {this,static_cast<IComponent::pMethod>(&Component_ChannelManager::Recv_Channel_LEAVE)};
}

void	Component_ChannelManager::Recv_Channel_JOIN(Packet_v1 *packet_v1)
{
  // mutex lock
  _channel_mutex.lock();
  int sessionId =  packet_v1->getSessionId();
  std::string channel = packet_v1->getChannel();
  // if !_channel[channel] 
  // add channel with sessionId
  _channel_mutex.unlock();
}

void	Component_ChannelManager::Recv_Channel_LEAVE(Packet_v1 *packet_v1)
{
  _channel_mutex.lock();
  int sessionId =  packet_v1->getSessionId();
  std::string channel = packet_v1->getChannel();
  // if _channel[channel]
  // remove sessionId
  // if _channel[channel] user = 0 delete _channel[channel]
  _channel_mutex.unlock();
}

