#include <Component_ChannelManager.h>
#include <Bind_recv.h>
#include <math.h>

Component_ChannelManager::Component_ChannelManager(ServerManager *serverManager) 
 :IComponent(CHANNEL_COMPONENTID), _serverManager(serverManager) 
{
  _rng.seed((int32_t)std::clock());
  _channelMap = new m_channel();
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
    new Request(CHANNEL_JOIN_OK, SEND, "JOIN_OK", NORETRY);

  (*_registeredRequests)[CHANNEL_JOIN_NOK_ALREADYINCHAN] = 
    new Request(CHANNEL_JOIN_NOK_ALREADYINCHAN, SEND, "JOIN_NOK_ALREADYINCHAN", NORETRY);

  (*_registeredRequests)[CHANNEL_JOINED] = 
    new Request(CHANNEL_JOINED, SEND, "JOINED", RETRY);

  (*_registeredRequests)[CHANNEL_MESSAGE_ACK] = 
    new Request(CHANNEL_MESSAGE_ACK, SEND, "MESSAGE_ACK", NORETRY);

  (*_registeredRequests)[CHANNEL_MESSAGE_RECV] = 
    new Request(CHANNEL_MESSAGE_RECV, SEND, "MESSAGE_RECV", RETRY);

  (*_registeredRequests)[CHANNEL_LEAVE_OK] = 
    new Request(CHANNEL_LEAVE_OK, SEND, "LEAVE_OK", NORETRY);

  (*_registeredRequests)[CHANNEL_LEAVE_NOK_NOTINCHAN] = 
    new Request(CHANNEL_LEAVE_NOK_NOTINCHAN, SEND, "LEAVE_NOK_NOTINCHAN", NORETRY);

  (*_registeredRequests)[CHANNEL_LEAVED] = 
    new Request(CHANNEL_LEAVED, SEND, "LEAVED", RETRY);

  // RECV requests
  (*_registeredRequests)[CHANNEL_JOIN] = 
    new Request(CHANNEL_JOIN, RECV, "JOIN", RESPONSETONOTHING);

  (*_registeredRequests)[CHANNEL_JOINED_ACK] = 
    new Request(CHANNEL_JOINED_ACK, RECV, "JOINED_ACK", CHANNEL_JOINED);

  (*_registeredRequests)[CHANNEL_MESSAGE] = 
    new Request(CHANNEL_MESSAGE, RECV, "MESSAGE", RESPONSETONOTHING);

  (*_registeredRequests)[CHANNEL_MESSAGE_RECV_ACK] = 
    new Request(CHANNEL_MESSAGE_RECV_ACK, RECV, "MESSAGE_RECV_ACK", CHANNEL_MESSAGE_RECV);

  (*_registeredRequests)[CHANNEL_LEAVE] = 
    new Request(CHANNEL_LEAVE, RECV, "LEAVE", RESPONSETONOTHING);

  (*_registeredRequests)[CHANNEL_LEAVED_ACK] = 
    new Request(CHANNEL_LEAVED_ACK, RECV, "LEAVED_ACK", CHANNEL_LEAVED);
}

void	Component_ChannelManager::Recv_Join(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  field_t channelId;
  field_t sessionId		= packet_v1_channel->getSessionId();
  char const *channelName	= packet_v1_channel->getChannelName();
  Channel *chan;
  bool existing			= false;

  m_channel::iterator it, end = _channelMap->end();
  for (it = _channelMap->begin(); it != end; ++it)
    {
      chan = it->second;
      if (strcmp(chan->getName(), channelName) == 0)
	{
	  channelId = it->first;
	  existing = true;
	  break;
	}
    }

  if (!existing)
    {
      channelId =  GenChannelId();
      chan = new Channel(channelName);
      _channelMap->insert(std::pair<field_t, Channel*>(channelId, chan));
    }

  if (chan->addConnected(session, sessionId))
    {
      Send_Join_OK(session, channelId, channelName);

      std::map<field_t, Session*> *connected = chan->getConnected();
      std::map<field_t, Session *>::iterator it, end = connected->end();

      for (it = connected->begin(); it != end ; ++it)
	{
	  if (it->first != sessionId)
	    {
	      Send_Joined(session, channelId, it->first, it->second->getLogin().c_str());
	      Send_Joined(it->second, channelId, sessionId, session->getLogin().c_str());
	    }
	}
    }
  else
    Send_Join_NOK_ALREADYINCHAN(session, channelId, channelName);
}

void	Component_ChannelManager::Send_Join_OK(Session *session, field_t channelId, char const *channelName)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_JOIN_OK);

  packet_v1_channel->setChannelId(channelId);
  //  packet_v1_channel->setChannelName(channelName);
  _serverManager->Send(packet_v1_channel, session);
}

void	Component_ChannelManager::Send_Join_NOK_ALREADYINCHAN(Session *session, field_t channelId, char const *channelName)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_JOIN_NOK_ALREADYINCHAN);

  packet_v1_channel->setChannelId(channelId);
  //  packet_v1_channel->setChannelName(channelName);
  _serverManager->Send(packet_v1_channel, session);
}

void	Component_ChannelManager::Send_Joined(Session *session, field_t channelId, field_t clientSessionId, char const * clientLogin)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_JOINED);

  packet_v1_channel->setChannelId(channelId);
  packet_v1_channel->setClientSessionId(clientSessionId);
  packet_v1_channel->setChannelName(_channelMap->find(channelId)->second->getName());
  packet_v1_channel->setClientLogin(clientLogin);

  _serverManager->Send(packet_v1_channel, session);
}

void	Component_ChannelManager::Recv_Message(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Channel const *packet_v1_channel = 
    static_cast<Packet_v1_Channel const *>(packet_v1);

  field_t channelId	= packet_v1_channel->getChannelId();
  field_t sessionId	= packet_v1_channel->getSessionId();
  char const *message	= packet_v1_channel->getMessage();

  if (_channelMap->find(channelId) != _channelMap->end())
    {
      Channel *chan = _channelMap->find(channelId)->second;
      std::map<field_t, Session*> *connected = chan->getConnected();

      Send_Message_ACK(session);

      std::map<field_t, Session *>::iterator it, end = connected->end();
      for (it = connected->begin(); it != end ; ++it)
	Send_Message_RECV(it->second, message, channelId, sessionId);
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
  char const *clientLogin = session->getLogin().c_str();
  
  if (_channelMap->find(channelId) != _channelMap->end())
    {
      Channel *chan = _channelMap->find(channelId)->second;
      if (chan->removeConnected(sessionId))
	{
	  Send_Leave_OK(session, channelId);

	  std::map<field_t, Session*> *connected = chan->getConnected();
 	  std::map<field_t, Session *>::iterator it, end = connected->end();

	  for (it = connected->begin(); it != end ; ++it)
	    Send_Leaved(it->second, channelId, sessionId, clientLogin);
	  if (connected->size() == 0)
	    _channelMap->erase(channelId);
	}
      else
	Send_Leave_NOK_NOTINCHAN(session, channelId);
    }
  else
    Send_Leave_NOK_NOTINCHAN(session, channelId);
}

void	Component_ChannelManager::Send_Leave_OK(Session *session, field_t channelId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_LEAVE_OK);

  packet_v1_channel->setChannelId(channelId);
  packet_v1_channel->setChannelName(_channelMap->find(channelId)->second->getName());

  _serverManager->Send(packet_v1_channel, session);
}

void	Component_ChannelManager::Send_Leave_NOK_NOTINCHAN(Session *session, field_t channelId)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_LEAVE_NOK_NOTINCHAN);

  packet_v1_channel->setChannelId(channelId);
  _serverManager->Send(packet_v1_channel, session);
}
    
void	Component_ChannelManager::Send_Leaved(Session *session, field_t channelId, field_t clientSessionId, char const * clientLogin)
{
  Packet_v1_Channel *packet_v1_channel = new Packet_v1_Channel(CHANNEL_LEAVED);

  packet_v1_channel->setChannelId(channelId);
  packet_v1_channel->setClientSessionId(clientSessionId);
  packet_v1_channel->setChannelName(_channelMap->find(channelId)->second->getName());
  packet_v1_channel->setClientLogin(clientLogin);

  _serverManager->Send(packet_v1_channel, session);
}

void	Component_ChannelManager::Connect(Session *)
{}

void	Component_ChannelManager::Disconnect(Session *session)
{
  m_channel::iterator it, end = _channelMap->end();

  for (it = _channelMap->begin(); it != end; ++it)
    {
      std::map<field_t, Session*> *connected = it->second->getConnected();

      if (connected->find(session->getSessionId()) != connected->end())
	{
	  it->second->removeConnected(session->getSessionId());
	  if (connected->size() == 0)
	      _channelMap->erase(it->first);
	  else
	    {
	      std::map<field_t, Session*>::iterator i, e = connected->end();

	      for (i = connected->begin(); i != e; ++i)
		Send_Leaved(i->second, it->first, session->getSessionId(), session->getLogin().c_str());
	    }
	}
    }
}

field_t	Component_ChannelManager::GenChannelId()
{
  field_t	channelId;

  do {
    channelId = _rng() % ((int)pow(2, PROTOV1_CHANNEL_CHANNELID_SIZE));
  } while (! IsUniqId(channelId));
 return channelId;
}

bool	Component_ChannelManager::IsUniqId(field_t channelId) const
{
  return (_channelMap->find(channelId) == _channelMap->end());
}
