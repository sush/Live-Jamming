#include <Component_Session.h>

Component_Channel::Component_Channel(IComponent::m_packet_bindings & packetBindings, ClientManager *clientManager) 
 :IComponent(clientManager), _packetBindings(packetBindings), _clientManager(clientManager) 
{
  PacketBindings();
}

void	Component_Channel::PacketBindings() 
{
  _packetBindings[CHANNEL_MSG] =
    {this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Channel_MSG)};
  _packetBindings[CHANNEL_JOIN] =
    {this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Channel_JOIN)};
  _packetBindings[CHANNEL_LEAVE] =
    {this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Channel_LEAVE)};
}

void	Component_Channel::Recv_Channel_MSG(Packet_v1 *packet_v1)
{

}

void	Component_Channel::Recv_Channel_JOIN(Packet_v1 *)
{

}

void	Component_Channel::Recv_Channel_LEAVE(Packet_v1 *)
{

}

