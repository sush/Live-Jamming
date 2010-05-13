#include <Component_ChannelManager.h>

Component_ChannelManager::Component_ChannelManager(ServerManager *serverManager) 
 :IComponent(CHANNEL_COMPONENTID), _serverManager(serverManager) 
{
}

Component_ChannelManager::~Component_ChannelManager() {}

void	Component_ChannelManager::BindingsRecv()
{
  (*_bindingsRecv)[CHANNEL_JOIN] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_ChannelManager::Recv_Join));

  (*_bindingsRecv)[CHANNEL_JOINED_ACK] =
    new Bind_recv(0, 0);
  
  (*_bindingsRecv)[CHANNEL_MESSAGE] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_ChannelManager::Recv_Message));

  (*_bindingsRecv)[CHANNEL_MESSAGE_RECV_ACK] =
    new Bind_recv(0, 0);

  (*_bindingsRecv)[CHANNEL_LEAVE] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_ChannelManager::Recv_Leave));

  (*_bindingsRecv)[CHANNEL_LEAVED_ACK] =
    new Bind_recv(0, 0);
}

void	Component_ChannelManager::RegisteredRequests()
{
  // SEND requests
  (*_registeredRequests)[CHANNEL_JOIN_OK] = 
    new Request(CHANNEL_JOIN_OK, SEND, "Channel Join response OK", NORETRY);

  (*_registeredRequests)[CHANNEL_JOIN_NOK_ALREADYINCHAN] = 
    new Request(CHANNEL_JOIN_NOK_ALREADYINCHAN, SEND, "Channel Join response NOK user already in channel", NORETRY);

  (*_registeredRequests)[CHANNEL_JOINED] = 
    new Request(CHANNEL_JOINED, SEND, "Channel Joined response", RETRY);

  (*_registeredRequests)[CHANNEL_MESSAGE_ACK] = 
    new Request(CHANNEL_MESSAGE_ACK, SEND, "Channel Message response ACK", NORETRY);

  (*_registeredRequests)[CHANNEL_MESSAGE_RECV] = 
    new Request(CHANNEL_MESSAGE_RECV, SEND, "Channel Message repsonse RECV", RETRY);

  (*_registeredRequests)[CHANNEL_LEAVE_OK] = 
    new Request(CHANNEL_LEAVE_OK, SEND, "Channel Leave response OK", NORETRY);

  (*_registeredRequests)[CHANNEL_LEAVE_NOK_NOTINCHAN] = 
    new Request(CHANNEL_LEAVE_NOK_NOTINCHAN, SEND, "Channel Leave response NOK user not in channel", NORETRY);

  (*_registeredRequests)[CHANNEL_LEAVED] = 
    new Request(CHANNEL_LEAVED, SEND, "Channel Leaved response", RETRY);

  // RECV requests
  (*_registeredRequests)[CHANNEL_JOIN] = 
    new Request(CHANNEL_JOIN, RECV, "Channel Join request", RESPONSETONOTHING);

  (*_registeredRequests)[CHANNEL_JOINED_ACK] = 
    new Request(CHANNEL_JOINED_ACK, RECV, "Channel Joined request ACK", CHANNEL_JOINED);

  (*_registeredRequests)[CHANNEL_MESSAGE] = 
    new Request(CHANNEL_MESSAGE, RECV, "Channel Message request", RESPONSETONOTHING);

  (*_registeredRequests)[CHANNEL_MESSAGE_RECV_ACK] = 
    new Request(CHANNEL_MESSAGE_RECV_ACK, RECV, "Channel Message request RECV ACK", CHANNEL_MESSAGE_RECV);

  (*_registeredRequests)[CHANNEL_LEAVE] = 
    new Request(CHANNEL_LEAVE, RECV, "Channel Leave request", RESPONSETONOTHING);

  (*_registeredRequests)[CHANNEL_LEAVED_ACK] = 
    new Request(CHANNEL_LEAVED_ACK, RECV, "Channel Leaved request ACK", CHANNEL_LEAVED);
}

void	Component_ChannelManager::Recv_Join(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  field_t channelId =  packet_v1_channel->getChannelId();
  field_t sessionId = session->getSessionId();
  Channel *chan;

  if (!_channelMap[channelId])
    {
      _channelMap[channelId] =  new Channel();
      chan = _channelMap[channelId];
    }
  else
    chan = _channelMap.find(channelId)->second; 

  if (chan->addConnected(session, sessionId))
    {
      Send_Join_OK(session, channelId);
      std::map<field_t, Session*> connected = chan->getConnected();

      std::map<field_t, Session *>::iterator it, end = connected.end();
      for (it = connected.begin(); it != end ; ++it)
	{
	  if (it->first != sessionId)
	    {
	      Send_Joined(session, channelId, it->first);
	      Send_Joined(it->second, channelId, sessionId);
	    }
	}
    }
  else
    Send_Join_NOK_ALREADYINCHAN(session, channelId);
}

void	Component_ChannelManager::Send_Join_OK(Session *session, field_t channelId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_JOIN_OK);

  packet_v1_channel->setChannelId(channelId);
  // also send list of users actualy connected to chan

  _serverManager->Send(packet_v1_channel, session);
}

void	Component_ChannelManager::Send_Join_NOK_ALREADYINCHAN(Session *session, field_t channelId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_JOIN_NOK_ALREADYINCHAN);

  packet_v1_channel->setChannelId(channelId);
  
  _serverManager->Send(packet_v1_channel, session);
}

void	Component_ChannelManager::Send_Joined(Session *session, field_t channelId, field_t clientSessionId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_JOINED);
  
  packet_v1_channel->setChannelId(channelId);
  packet_v1_channel->setClientSessionId(clientSessionId);
  
  _serverManager->Send(packet_v1_channel, session);
}

void	Component_ChannelManager::Recv_Message(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  field_t channelId = packet_v1_channel->getChannelId();
  field_t sessionId = packet_v1_channel->getSessionId();
  char const *message = packet_v1_channel->getMessage();

  if (_channelMap[channelId])
    {
      Channel *chan = _channelMap.find(channelId)->second;
      std::map<field_t, Session*> connected = chan->getConnected();

      std::map<field_t, Session *>::iterator it, end = connected.end();
      for (it = connected.begin(); it != end ; ++it)
	{
	  if (it->first != sessionId)
	    Send_Message_RECV((*it).second, message, channelId, sessionId);
	}
      Send_Message_ACK(session);
    }
}

void	Component_ChannelManager::Send_Message_ACK(Session *session)
{
  _serverManager->Send(_componentId, CHANNEL_MESSAGE_ACK, session);
}

void	Component_ChannelManager::Send_Message_RECV(Session *session, char const *message, field_t channelId, field_t clientSessionId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_MESSAGE_RECV);

  packet_v1_channel->setChannelId(channelId);
  packet_v1_channel->setMessage(message);
  packet_v1_channel->setClientSessionId(clientSessionId);

  _serverManager->Send(packet_v1_channel, session);
}

void	Component_ChannelManager::Recv_Leave(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  field_t channelId = packet_v1_channel->getChannelId();
  field_t sessionId = session->getSessionId();
  
  if (_channelMap[channelId])
    {
      Channel *chan = _channelMap.find(channelId)->second;

      if (chan->removeConnected(sessionId))
	{
	  Send_Leave_OK(session, channelId);
	  std::map<field_t, Session*> connected = chan->getConnected();
  
	  std::map<field_t, Session *>::iterator it, end = connected.end();
	  for (it = connected.begin(); it != end ; ++it)
	    Send_Leaved(it->second, channelId, sessionId);
	  if (connected.size() == 0)
	    _channelMap.erase(channelId);
	}
      else
	Send_Leave_NOK_NOTINCHAN(session, channelId);
    }
}

void	Component_ChannelManager::Send_Leave_OK(Session *session, field_t channelId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_LEAVE_OK);

  packet_v1_channel->setChannelId(channelId);

  _serverManager->Send(packet_v1_channel, session);
}

void	Component_ChannelManager::Send_Leave_NOK_NOTINCHAN(Session *session, field_t channelId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_LEAVE_NOK_NOTINCHAN);

  packet_v1_channel->setChannelId(channelId);

  _serverManager->Send(packet_v1_channel, session);
}
    
void	Component_ChannelManager::Send_Leaved(Session *session, field_t channelId, field_t clientSessionId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_LEAVED);

  packet_v1_channel->setChannelId(channelId);
  packet_v1_channel->setClientSessionId(clientSessionId);

  _serverManager->Send(packet_v1_channel, session);
}
