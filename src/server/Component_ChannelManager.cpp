#include <Component_ChannelManager.h>

Component_ChannelManager::Component_ChannelManager(IComponent::m_bindings_recv & bindingsRecv, ServerManager *serverManager) 
 :IComponent(clientManager), _bindingsRecv(bindingsRecv), _serverManager(serverManager) 
{
  BindingsRecv();
}

void	Component_ChannelManager::BindingsRecv()
{
  _bindingsRecv[CHANNEL_JOIN] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_ChannelManager::Recv_Join));

  _bindingsRecv[CHANNEL_LEAVE] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_ChannelManager::Recv_Leave));

  _bindingsRecv[CHANNEL_RECV_MSG] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_ChannelManager::Recv_Message));
}

void	Component_ChannelManager::Recv_Join(Packet_v1 *packet_v1, Session *session)
{
  std::string channel = packet_v1->getChannel();

  if (!_channel[channel])
    _channel[channel] =  new Channel(session);
  else
    Channel *chan = _channel.find(channel)->second;
  
  if (chan->addConnected(session))
    Send_Joined_OK(chan, session);
  else
    Send_Joined_NOK_ALREADYINCHAN(session);
}

void	Component_ChannelManager::Recv_Leave(Packet_v1 *packet_v1, Session *session)
{
  std::string channel = packet_v1->getChannel();

  if (_channel[channel])
    {
      Channel *chan = _channel.find(channel)->second;

      chan->removeConnected(session);
      if (connected.size() == 0)
	{
	  if (_channel.remove(channel))
	    Send_Leave_OK(chan, session);
	  else
	    Send_Leave_NOK_NOTINCHAN(session);
	}
    }
}

void	Component_ChannelManager::Recv_Message(Packet_v1 *packet_v1, Session *session)
{
  std::string channel = packet_v1->getChannel();
  std::string msg = packet_v1->getMsg();

  if (_channel[channel])
    {
      Channel *chan = _channel.find(channel)->second;
      Send_Message(chan, session, msg);
    }
}

void	Component_ChannelManager::Send_Joined_OK(Channel *chan, Session *session)
{
// send JOIN notification to all connected to the room
  std::vector<Session*> connected = chan->getConnected();
  
  // 
  for (unsigned int i = 0; i < connected.size(); ++i)
    // packet = forge packet CHANNEL_JOINED_OK with selected session pseudo as data
    //    _serverManager->send(packet, connected[i], RETRY); except user who just has joined for him :
    // _serverManager->send(packet, session, RETRY); list of all users as data
}

void	Component_ChannelManager::Send_Leaved_NOK_ALREAYDINCHAN(Session *session)
{
  // send JOIN_NOK_ALREADYINCHAN notification to client trying to join the channel
    _serverManager->send(CHANNEL_JOINED_NOK_ALREADYINCHAN, session, RETRY);
}

void	Component_ChannelManager::Send_Leaved_OK(Channel *channel, Session *session)
{
  // send LEAVE notification to all connected to the room
  std::vector<Session*> connected = channel->getConnected();

  for (unsigned int i = 0; i < connected.size(); ++i)
    // packet = forge packet LEAVED_OK with selected session pseudo as data
    //_serverManager->send(packet, connected->at(i), RETRY);
}

void	Component_ChannelManager::Send_Leaved_NOK_NOTINCHAN(Session *session)
{
  // send LEAVED_NOK_NOTINCHAN notification to client trying to LEAVE the channel
    _serverManager->send(CHANNEL_LEAVED_NOK_NOTINCHAN, session, RETRY);
}


void	Component_ChannelManager::Send_MSG(Channel *channel, Session *session, std::string msg)
{
  std::vector<Session*> connected = channel->getConnected();

  for (unsigned int i = 0; i < connected->size(); ++i)
    // packet = forge packet MSG with selected session pseudo and message as data
    //    _serverManager->send(packet, connected->at(i), RETRY);
}
