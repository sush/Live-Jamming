#include <Component_Channel.h>

Component_Channel::Component_Channel(IComponent::m_bindings_recv & bindingsRecv, ClientManager *clientManager)
  : IComponent(clientManager), _bindingsRecv(bindingsRecv), _clientManager(clientManager)
{
  BindingsRecv();
}

Component_Channel::~Component_Channel() {}

void		Component_Channel::BindingsRecv()
{
  _bindingsRecv[CHANNEL_MESSAGE] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Message));

  _bindingsRecv[CHANNEL_JOINED] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Joined));

  _bindingsRecv[CHANNEL_LEAVED] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Leaved));
}

void		Component_Channel::Recv_Message(Packet_v1 *packet_v1)
{
  // call global method for UI use with channel name and sender pseudo ans message
}

void		Component_Channel::Recv_Joined(Packet_v1 *packet_v1)
{
  if (packet_v1->getType() == CHANNEL_JOIN_OK)
  // call global method for UI use with channel name and pseudo of new user connected
  else
    // catch error
}

void		Component_Channel::Recv_Leaved(Packet_v1 *packet_v1)
{
  if (packet_v1->getType() == CHANNEL_LEAVED_OK)
  // call global method for UI use with channel name and pseudo of user leaved
  else
    // catch error
}

void		Component_Channel::Send_Message(Session *session)
{
  // forge packet to send with channel name and message as data
  //  _clientManager->send(packet, session, RETRY);
}

void		Component_Channel::Send_Joined(Session *session)
{
  // forge packet to send with channel name as data
  //  _clientManager->send(packet, session, RETRY);
}

void		Component_Channel::Send_Leaved(Session *session)
{
  // forge packet to send with channel name as data
  //  _clientManager->send(packet, session, RETRY);
}
