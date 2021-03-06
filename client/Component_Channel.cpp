#include <Component_Channel.h>
#include <Bind_recv.h>

extern Session* gl_session;

Component_Channel::Component_Channel(ClientManager *clientManager)
  : IComponent(CHANNEL_COMPONENTID), _clientManager(clientManager)
{
}

Component_Channel::~Component_Channel() {}

void		Component_Channel::BindingsRecv()
{
    (*_bindingsRecv)[CHANNEL_JOIN_OK] =
            new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Join_OK),
                          static_cast<Proxy*>(_clientManager), static_cast<Proxy::pMethod>(&Proxy::chanResponse));

    (*_bindingsRecv)[CHANNEL_JOIN_NOK_ALREADYINCHAN] =
            new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Join_NOK_ALREADYINCHAN),
                          static_cast<Proxy*>(_clientManager), static_cast<Proxy::pMethod>(&Proxy::chanResponse));

    (*_bindingsRecv)[CHANNEL_JOINED] =
            new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Joined),
            static_cast<Proxy*>(_clientManager), static_cast<Proxy::pMethod>(&Proxy::chanResponse));

  (*_bindingsRecv)[CHANNEL_MESSAGE_ACK] =
    new Bind_recv(0, 0);

  (*_bindingsRecv)[CHANNEL_MESSAGE_RECV] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Message_RECV),
    static_cast<Proxy*>(_clientManager), static_cast<Proxy::pMethod>(&Proxy::chanResponse));;
  
  (*_bindingsRecv)[CHANNEL_LEAVE_OK] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Leave_OK),
    static_cast<Proxy*>(_clientManager), static_cast<Proxy::pMethod>(&Proxy::chanResponse));
  
  (*_bindingsRecv)[CHANNEL_LEAVE_NOK_NOTINCHAN] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Leave_NOK_NOTINCHAN));
  
  (*_bindingsRecv)[CHANNEL_LEAVED] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Leaved),
    static_cast<Proxy*>(_clientManager), static_cast<Proxy::pMethod>(&Proxy::chanResponse));

  (*_bindingsRecv)[CHANNEL_LISTED] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Channel::Recv_Listed),
    static_cast<Proxy*>(_clientManager), static_cast<Proxy::pMethod>(&Proxy::chanResponse));
}

void	Component_Channel::RegisteredRequests()
{
  // SEND requests
  (*_registeredRequests)[CHANNEL_JOIN] = 
    new Request(CHANNEL_JOIN, SEND, "JOIN", RETRY);

  (*_registeredRequests)[CHANNEL_JOINED_ACK] = 
    new Request(CHANNEL_JOINED_ACK, SEND, "JOINED_ACK", NORETRY);

  (*_registeredRequests)[CHANNEL_MESSAGE] = 
    new Request(CHANNEL_MESSAGE, SEND, "MESSAGE", RETRY);

  (*_registeredRequests)[CHANNEL_MESSAGE_RECV_ACK] = 
    new Request(CHANNEL_MESSAGE_RECV_ACK, SEND, "MESSAGE_RECV_ACK", NORETRY);

  (*_registeredRequests)[CHANNEL_LEAVE] = 
    new Request(CHANNEL_LEAVE, SEND, "LEAVE", RETRY);

  (*_registeredRequests)[CHANNEL_LEAVED_ACK] = 
    new Request(CHANNEL_LEAVED_ACK, SEND, "LEAVED_ACK", NORETRY);

  (*_registeredRequests)[CHANNEL_LIST] = 
    new Request(CHANNEL_LIST, SEND, "LIST", RETRY);

  // RECV requests
  (*_registeredRequests)[CHANNEL_JOIN_OK] = 
    new Request(CHANNEL_JOIN_OK, RECV, "JOIN_OK", CHANNEL_JOIN);

  (*_registeredRequests)[CHANNEL_JOIN_NOK_ALREADYINCHAN] = 
    new Request(CHANNEL_JOIN_NOK_ALREADYINCHAN, RECV, "JOIN_NOK_ALREADYINCHAN", CHANNEL_JOIN);

  (*_registeredRequests)[CHANNEL_JOINED] = 
    new Request(CHANNEL_JOINED, RECV, "JOINED", RESPONSETONOTHING);

  (*_registeredRequests)[CHANNEL_MESSAGE_ACK] = 
    new Request(CHANNEL_MESSAGE_ACK, RECV, "MESSAGE_ACK", CHANNEL_MESSAGE);

  (*_registeredRequests)[CHANNEL_MESSAGE_RECV] = 
    new Request(CHANNEL_MESSAGE_RECV, RECV, "MESSAGE_RECV", RESPONSETONOTHING);

  (*_registeredRequests)[CHANNEL_LEAVE_OK] = 
    new Request(CHANNEL_LEAVE_OK, RECV, "LEAVE_OK", CHANNEL_LEAVE);

  (*_registeredRequests)[CHANNEL_LEAVE_NOK_NOTINCHAN] = 
    new Request(CHANNEL_LEAVE_NOK_NOTINCHAN, RECV, "LEAVE_NOK_NOTINCHAN", CHANNEL_LEAVE);

  (*_registeredRequests)[CHANNEL_LEAVED] = 
    new Request(CHANNEL_LEAVED, RECV, "LEAVED", RESPONSETONOTHING);

  (*_registeredRequests)[CHANNEL_LISTED] = 
    new Request(CHANNEL_LISTED, RECV, "LISTED", CHANNEL_LIST);
}

char const	*Component_Channel::getChannelName(field_t channelId) const
{
  if (_channelMap.find(channelId) != _channelMap.end())
    return _channelMap.find(channelId)->second->getName();
  return 0;
}

void		Component_Channel::Send_Join(char * const name)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_JOIN);
  packet_v1_channel->setChannelName(name);

  _clientManager->Send(packet_v1_channel, gl_session);
}

void		Component_Channel::Recv_Join_OK(Packet_v1 const *packet_v1, Session * session)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  Packet_v1_Channel const	*orig_packet = static_cast<Packet_v1_Channel const *>
    (getOrigPacket(packet_v1, session));
      
  std::cout << "orig_packet = " << (int)orig_packet << std::endl;
  field_t channelId = packet_v1_channel->getChannelId();
  //  char const *channelName = packet_v1_channel->getChannelName();

  std::cout << "getChannelName() = " << orig_packet->getChannelName() << std::endl;
  if (_channelMap.find(channelId) == _channelMap.end()) {
      std::cerr << "ORIG_PACKET->GETCHANNELNAME: " << packet_v1_channel->getChannelId() << std::endl;
    _channelMap[channelId] = new Channel(orig_packet->getChannelName());
}
}

void		Component_Channel::Recv_Join_NOK_ALREADYINCHAN(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  Packet_v1_Channel const	*orig_packet = static_cast<Packet_v1_Channel const *>
    (getOrigPacket(packet_v1, session));

  field_t channelId = packet_v1_channel->getChannelId();
  // in case of lost packet check if user not in chan if so add him to it
  if (_channelMap.find(channelId) != _channelMap.end())
    {
      Channel *chan = _channelMap.find(channelId)->second;
      chan->addConnected(0, session->getSessionId());
    }
}

void		Component_Channel::Recv_Joined(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  field_t	clientSessionId = packet_v1_channel->getClientSessionId();
  field_t	channelId = packet_v1_channel->getChannelId();
  Channel	*chan = _channelMap.find(channelId)->second;

  chan->addConnected(0, clientSessionId);
  Send_Joined_ACK();
}

void		Component_Channel::Send_Joined_ACK()
{
  _clientManager->Send(_componentId, CHANNEL_JOINED_ACK, gl_session);
}

void		Component_Channel::Send_Message(char const *message, field_t channelId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_MESSAGE);

  packet_v1_channel->setChannelId(channelId);
  packet_v1_channel->setMessage(message);
  _clientManager->Send(packet_v1_channel, gl_session);
}

void		Component_Channel::Recv_Message_RECV(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  //  field_t clientSessionId = packet_v1_channel->getClientSessionId();
  field_t channelId = packet_v1_channel->getChannelId();
  char const * message = packet_v1_channel->getMessage();

  // implement gui receive message
  Send_Message_RECV_ACK();
}

void		Component_Channel::Send_Message_RECV_ACK()
{
  _clientManager->Send(_componentId, CHANNEL_MESSAGE_RECV_ACK, gl_session);
}

void		Component_Channel::Send_Leave(field_t channelId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_LEAVE);

  packet_v1_channel->setChannelId(channelId);

  _clientManager->Send(packet_v1_channel, gl_session);
}

void		Component_Channel::Recv_Leave_OK(Packet_v1 const *packet_v1, Session *)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  field_t channelId = packet_v1_channel->getChannelId();

  _channelMap.erase(channelId);
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
}

void		Component_Channel::Recv_Leaved(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  field_t	channelId = packet_v1_channel->getChannelId();
  field_t	clientSessionId = packet_v1_channel->getClientSessionId();

  Channel *chan = _channelMap.find(channelId)->second;
  chan->removeConnected(clientSessionId);
  Send_Leaved_ACK();
}

void		Component_Channel::Send_Leaved_ACK()
{
  _clientManager->Send(_componentId, CHANNEL_LEAVED_ACK, gl_session);
}

Component_Channel::m_channel const &	Component_Channel::getAllChannel() const
{
  return _channelMap;
}

void		Component_Channel::Send_List()
{
  _clientManager->Send(_componentId, CHANNEL_LIST, gl_session);
}

void		Component_Channel::Recv_Listed(Packet_v1 const *, Session *)
{
  // Packet_v1_Channel const		*packet_v1_channel = 
  //   static_cast<Packet_v1_Channel const *>(packet_v1);

  // list of existing channels
  // std::vector<std::string>		*v_channel = packet_v1_channel->getChannelList();
}

void		Component_Channel::Connect(Session *)
{}

void		Component_Channel::Disconnect(Session *)
{}
