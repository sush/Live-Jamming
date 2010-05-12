#include <Component_Channel.h>

Component_Channel::Component_Channel(ClientManager *clientManager)
  : IComponent(CHANNEL_COMPONENTID), _clientManager(clientManager)
{
  _channelMap = new m_channel;
}

Component_Channel::~Component_Channel() {}

void		Component_Channel::BindingsRecv()
{
  _bindingsRecv[CHANNEL_JOIN_OK] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Join_OK));
  
  _bindingsRecv[CHANNEL_JOIN_NOK_ALREADYINCHAN] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Join_NOK_ALREADYINCHAN));
  
  _bindingsRecv[CHANNEL_JOINED] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Joined));
  
  _bindingsRecv[CHANNEL_MESSAGE_ACK] =
    new Bind_recv(0, 0);

  _bindingsRecv[CHANNEL_MESSAGE_RECV] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Message_RECV));
  
  _bindingsRecv[CHANNEL_LEAVE_OK] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Leave_OK));
  
  _bindingsRecv[CHANNEL_LEAVE_NOK_NOTINCHAN] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Leave_NOK_NOTINCHAN));
  
  _bindingsRecv[CHANNEL_LEAVED] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Leaved));
}

void	Component_Session::RegisteredRequests()
{
  // SEND requests
  (*_registeredRequests)[CHANNEL_JOIN] = 
    new Request(CHANNEL_JOIN, SEND, "Channel Join response", RETRY);

  (*_registeredRequests)[CHANNEL_JOINED_ACK] = 
    new Request(CHANNEL_JOINED_ACK, SEND, "Channel Joined response ACK", NORETRY);

  (*_registeredRequests)[CHANNEL_MESSAGE] = 
    new Request(CHANNEL_MESSAGE, SEND, "Channel Message response", RETRY);

  (*_registeredRequests)[CHANNEL_MESSAGE_RECV_ACK] = 
    new Request(CHANNEL_MESSAGE_RECV_ACK, SEND, "Channel Message RECV ACK response", NORETRY);

  (*_registeredRequests)[CHANNEL_LEAVE] = 
    new Request(CHANNEL_LEAVE, SEND, "Channel Leave response", RETRY);

  (*_registeredRequests)[CHANNEL_LEAVED_ACK] = 
    new Request(CHANNEL_LEAVED_ACK, SEND, "Channel Leaved response ACK", NORETRY);

  // RECV requests
  (*_registeredRequests)[CHANNEL_JOIN_OK] = 
    new Request(CHANNEL_JOIN_OK, RECV, "Channel Join request OK", RESPONSETONOTHING);

  (*_registeredRequests)[CHANNEL_JOIN_NOK_ALREADYINCHAN] = 
    new Request(CHANNEL_JOIN_NOK_ALREADYINCHAN, RECV, "Channel Join request NOK user already in chan", RESPONSETONOTHING);

  (*_registeredRequests)[CHANNEL_JOINED] = 
    new Request(CHANNEL_JOIN_OK, RECV, "Channel Joined request", RESPONSETONOTHING);

  (*_registeredRequests)[CHANNEL_MESSAGE_ACK] = 
    new Request(CHANNEL_MESSAGE_ACK, RECV, "Channel Message request ACK", CHANNEL_MESSAGE);

  (*_registeredRequests)[CHANNEL_MESSAGE_RECV] = 
    new Request(CHANNEL_MESSAGE_RECV, RECV, "Channel Message request RECV", RESPONSETONOTHING);

  (*_registeredRequests)[CHANNEL_LEAVE_OK] = 
    new Request(CHANNEL_LEAVE_OK, RECV, "Channel Leave request OK", RESPONSETONOTHING);

  (*_registeredRequests)[CHANNEL_LEAVE_NOK_NOTINCHAN] = 
    new Request(CHANNEL_LEAVE_NOK_NOTINCHAN, RECV, "Channel Leave request NOK user not in chan", RESPONSETONOTHING);

  (*_registeredRequests)[CHANNEL_LEAVED] = 
    new Request(CHANNEL_LEAVED, RECV, "Channel Leaved request", RESPONSETONOTHING);
}

void		Component_Channel::Send_Join(Session const *session, field_t channelId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_JOIN);
  packet_v1_channel->setChannelId(channelId);

  _clientManager->Send(packet_v1, session);
}

void		Component_Channel::Recv_Join_OK(Packet_v1 const *packet_v1, Session const *session)
{
  field_t channelId = packet_v1->getChannelId();

  if (!_channelMap[channelId])
    _channelMap[channelId] = new Channel(0, listOfConnected);
}

void		Component_Channel::Recv_Join_NOK_ALREADYINCHAN(Packet_v1 const *packet_v1, Session const *session)
{
  field_t channelId = packet_v1->getChannelId();
  // in case of lost packet check if user not in chan if so add him to it
  Channel *chan = _channelMap.find(channelId)->second;
  chan->addConnected(session->getSessionId());
}

void		Component_Channel::Recv_Joined(Packet_v1 const *packet_v1, Session const *session)
{
  field_t clientSessionId = packet_v1->getClientSessionId();
  field_t ChannelId = packet_v1->getChannelId();
  Channel *chan = _channelMap.find(channelId)->second;

  chan->addConnected(0, clientSessionId);
  Send_Joined_ACK(session);
}

void		Component_Channel::Send_Joined_ACK(Session const *session)
{
  _clientManager->Send(_componentId, CHANNEL_JOINED_ACK, session);
}

void		Component_Channel::Send_Message(Session const *session, std::string const & message, field_t channelId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_MESSAGE);

  packet_v1_channel->setChannelId(channelId);
  packet_v1_channel->setMessage(message);

  _clientManager->Send(packet_v1_channel, session);
}

void		Component_Channel::Recv_Message_RECV(Packet_v1 const *packet_v1, Session const *session)
{
  // implement gui receive message
  Send_Message_RECV_ACK();
}

void		Component_Channel::Send_Message_RECV_ACK(Session const *session)
{
  _clientManager->Send(_componentId, CHANNEL_MESSAGE_RECV_ACK, session);
}

void		Component_Channel::Send_Leave(Session const *session, field_t channelId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_LEAVE);

  packet_v1_channel->setChannelId(channelId);

  _clientManager->Send(packet_v1_channel, session);
}

void		Component_Channel::Recv_Leave_OK(Packet_v1 const *packet_v1, Session const *session)
{
  field_t channelId = packet_v1->getChannelId();

  _channelMap.erase(channelId);
}

void		Component_Channel::Recv_Leave_NOK_NOTINCHAN(Packet_v1 const *packet_v1, Session const *session)
{
  field_t channelId = packet_v1->getChannelId();
  // in case of lost packet check if user still in chan, if so delete him
  Channel *chan = _channelMap.find(channelId)->second;
  chan->removeConnected(session->getSessionId());
}

void		Component_Channel::Recv_Leaved(Packet_v1 const *packet_v1, Session const *session)
{
  field_t channelId = packet_v1->getChannelId();
  field_t clientSessionId = packet_v1->getClientSessionId();

  Channel *chan = _channelMap.find(channelId)->second;
  chan->removeConnected(clientSessionId);
  Send_Leaved_ACK(session);
}

void		Component_Channel::Send_Leaved_ACK(Session const *session)
{
  _clientManager->Send(_componentId, CHANNEL_LEAVED_ACK, session);
}
