#include <Component_Channel.h>
#include <Bind_recv.h>

Component_Channel::Component_Channel(ClientManager *clientManager)
  : IComponent(CHANNEL_COMPONENTID), _clientManager(clientManager)
{
}

Component_Channel::~Component_Channel() {}

void		Component_Channel::BindingsRecv()
{
  (*_bindingsRecv)[CHANNEL_JOIN_OK] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Join_OK));
  
  (*_bindingsRecv)[CHANNEL_JOIN_NOK_ALREADYINCHAN] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Join_NOK_ALREADYINCHAN));
  
  (*_bindingsRecv)[CHANNEL_JOINED] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Joined));
  
  (*_bindingsRecv)[CHANNEL_MESSAGE_ACK] =
    new Bind_recv(0, 0);

  (*_bindingsRecv)[CHANNEL_MESSAGE_RECV] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Message_RECV));
  
  (*_bindingsRecv)[CHANNEL_LEAVE_OK] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Leave_OK));
  
  (*_bindingsRecv)[CHANNEL_LEAVE_NOK_NOTINCHAN] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Leave_NOK_NOTINCHAN));
  
  (*_bindingsRecv)[CHANNEL_LEAVED] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Leaved));
}

void	Component_Channel::RegisteredRequests()
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

void		Component_Channel::Send_Join(Session *session, field_t channelId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_JOIN);
  packet_v1_channel->setChannelId(channelId);

  std::cout << ">>>>>>>>>>>> SEND [JOIN] Channel [" << channelId  << "]<<<<<<<<<<<<" << std::endl;

  _clientManager->Send(packet_v1_channel, session);
}

void		Component_Channel::Recv_Join_OK(Packet_v1 const *packet_v1, Session *)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  field_t channelId = packet_v1_channel->getChannelId();

  std::cout << ">>>>>>>>>>>> RECV [JOIN_OK] Channel [" <<  channelId  <<"]<<<<<<<<<<<<" << std::endl;

  if (_channelMap.find(channelId) == _channelMap.end())
    _channelMap[channelId] = new Channel();
}

void		Component_Channel::Recv_Join_NOK_ALREADYINCHAN(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  field_t channelId = packet_v1_channel->getChannelId();
  // in case of lost packet check if user not in chan if so add him to it
  if (_channelMap.find(channelId) != _channelMap.end())
    {
      Channel *chan = _channelMap.find(channelId)->second;
      chan->addConnected(session, session->getSessionId());
    }
  std::cout << ">>>>>>>>>>>> RECV [JOIN_NOK_ALREADYINCHAN] Channel [" << channelId  << "]<<<<<<<<<<<<" << std::endl;
}

void		Component_Channel::Recv_Joined(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  field_t clientSessionId = packet_v1_channel->getClientSessionId();
  field_t channelId = packet_v1_channel->getChannelId();
  Channel *chan = _channelMap.find(channelId)->second;

  chan->addConnected(0, clientSessionId);
  std::cout << ">>>>>>>>>>>> RECV [JOINED] Channel [" << channelId  << "] User [" << clientSessionId  << "]<<<<<<<<<<<<" << std::endl;
  Send_Joined_ACK(session);
}

void		Component_Channel::Send_Joined_ACK(Session *session)
{
  std::cout << ">>>>>>>>>>>> SEND [JOINED_ACK] <<<<<<<<<<<<" << std::endl;
  _clientManager->Send(_componentId, CHANNEL_JOINED_ACK, session);
}

void		Component_Channel::Send_Message(Session *session, char const *message, field_t channelId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_MESSAGE);

  packet_v1_channel->setChannelId(channelId);
  packet_v1_channel->setMessage(message);
  std::cout << ">>>>>>>>>>>> SEND [MESSAGE] Channel [" << channelId  << "] Message [" << message  << "]<<<<<<<<<<<<" << std::endl;
  _clientManager->Send(packet_v1_channel, session);
}

void		Component_Channel::Recv_Message_RECV(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  field_t clientSessionId = packet_v1_channel->getClientSessionId();
  field_t channelId = packet_v1_channel->getChannelId();
  char const * message = packet_v1_channel->getMessage();

  std::cout << ">>>>>>>>>>>> RECV [MESSAGE] Channel [" << channelId  << "] Message [" << message  << "]<<<<<<<<<<<<" << std::endl;
  // implement gui receive message
  Send_Message_RECV_ACK(session);
}

void		Component_Channel::Send_Message_RECV_ACK(Session *session)
{
  std::cout << ">>>>>>>>>>>> SEND [MESSAGE_RECV_ACK] <<<<<<<<<<<<" << std::endl;
  _clientManager->Send(_componentId, CHANNEL_MESSAGE_RECV_ACK, session);
}

void		Component_Channel::Send_Leave(Session *session, field_t channelId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_LEAVE);

  packet_v1_channel->setChannelId(channelId);

  std::cout << ">>>>>>>>>>>> SEND [LEAVE] Channel [" << channelId  << "]<<<<<<<<<<<<" << std::endl;
  _clientManager->Send(packet_v1_channel, session);
}

void		Component_Channel::Recv_Leave_OK(Packet_v1 const *packet_v1, Session *)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  field_t channelId = packet_v1_channel->getChannelId();

  _channelMap.erase(channelId);
  std::cout << ">>>>>>>>>>>> RECV [LEAVE_OK] Channel [" << channelId  <<"]<<<<<<<<<<<<" << std::endl;
}

void		Component_Channel::Recv_Leave_NOK_NOTINCHAN(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  field_t channelId = packet_v1_channel->getChannelId();
  // in case of lost packet check if user still in chan, if so delete him
  if (_channelMap.find(channelId) != _channelMap.end())
    {
      Channel *chan = _channelMap.find(channelId)->second;
      chan->removeConnected(session->getSessionId());
      _channelMap.erase(channelId);
    }
  std::cout << ">>>>>>>>>>>> RECV [LEAVE_NOK_NOTINCHAN] Channel [" << channelId << "]<<<<<<<<<<<<" << std::endl;
}

void		Component_Channel::Recv_Leaved(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  field_t channelId = packet_v1_channel->getChannelId();
  field_t clientSessionId = packet_v1_channel->getClientSessionId();

  Channel *chan = _channelMap.find(channelId)->second;
  chan->removeConnected(clientSessionId);
  std::cout << ">>>>>>>>>>>> RECV [LEAVED] Channel [" << channelId << "]<<<<<<<<<<<<" << std::endl;
  Send_Leaved_ACK(session);
}

void		Component_Channel::Send_Leaved_ACK(Session *session)
{
  std::cout << ">>>>>>>>>>>> SEND [LEAVED_ACK] <<<<<<<<<<<<" << std::endl;
  _clientManager->Send(_componentId, CHANNEL_LEAVED_ACK, session);
}
