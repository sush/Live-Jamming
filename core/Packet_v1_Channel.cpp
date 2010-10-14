#include <Packet_v1_Channel.h>

Packet_v1_Channel::Packet_v1_Channel(boost::asio::ip::udp::endpoint const *endpoint, buffer_t *buffer, std::size_t len)
  :Packet_v1::Packet_v1(endpoint, buffer, len)
{}

Packet_v1_Channel::Packet_v1_Channel(field_t requestId)
  : Packet_v1(CHANNEL_COMPONENTID, requestId)
{}

Packet_v1_Channel::~Packet_v1_Channel()
{}

void		Packet_v1_Channel::Print(std::string const &componentName, Manager const * manager) const
{
  std::cout << PACKET_STRING << " [Packet_v1_Channel] " << PACKET_STRING << std::endl;
  Print_v1_Channel(componentName, manager);
  std::cout << PACKET_STRING << PACKET_STRING << PACKET_STRING << std::endl;
}

void		Packet_v1_Channel::Print_v1_Channel(std::string const &componentName, Manager const * manager) const
{
  Print_v1(componentName, manager);
  std::cout << "[CHANNELID: " << getChannelId() << " {" << PROTOV1_CHANNEL_CHANNELID_SIZE << "}]"
	    << "[CLIENTSESSIONID: " << getClientSessionId() << "{" << PROTOV1_CHANNEL_CLIENTSESSIONID_SIZE << "}]"
	    << std::endl;
  int id = getRequestId();
  if (id == CHANNEL_JOIN || id == CHANNEL_JOIN_OK || id == CHANNEL_JOIN_NOK_ALREADYINCHAN ||
      id == CHANNEL_JOINED || id == CHANNEL_LEAVE_OK || id == CHANNEL_LEAVED)
    std::cout << "# ChannelName: '" << getChannelName() << "'" << std::endl;
  if (id == CHANNEL_JOINED || id == CHANNEL_LEAVED)
    std::cout << "# Login: '" << getClientLogin() << "'" << std::endl;
  if (id == CHANNEL_MESSAGE || id == CHANNEL_MESSAGE_RECV)
    std::cout << "# Message: '" << getMessage() << "'" << std::endl;    
}

field_t		Packet_v1_Channel::getChannelId() const
{
  return getField(PROTOV1_CHANNEL_CHANNELID_OFF, PROTOV1_CHANNEL_CHANNELID_SIZE);
}

field_t		Packet_v1_Channel::getClientSessionId() const
{
  return getField(PROTOV1_CHANNEL_CLIENTSESSIONID_OFF, PROTOV1_CHANNEL_CLIENTSESSIONID_SIZE);
}

void		Packet_v1_Channel::setChannelId(field_t channelId)
{
  setField(channelId, PROTOV1_CHANNEL_CHANNELID_OFF, PROTOV1_CHANNEL_CHANNELID_SIZE);
}

void		Packet_v1_Channel::setClientSessionId(field_t clientSessionId)
{
  setField(clientSessionId, PROTOV1_CHANNEL_CLIENTSESSIONID_OFF, PROTOV1_CHANNEL_CLIENTSESSIONID_SIZE);
}

void		Packet_v1_Channel::setMessage(char const * message)
{
  assert(getRequestId() == CHANNEL_MESSAGE || getRequestId() == CHANNEL_MESSAGE_RECV);
  appendData(PROTOV1_CHANNEL_START_OF_DATA, PROTOV1_CHANNEL_DATA_MESSAGE, reinterpret_cast<byte_t const *>(message));
}

char const	*Packet_v1_Channel::getMessage() const
{
  assert(getRequestId() == CHANNEL_MESSAGE || getRequestId() == CHANNEL_MESSAGE_RECV);
  return reinterpret_cast<char const *>(getData(PROTOV1_CHANNEL_START_OF_DATA, PROTOV1_CHANNEL_DATA_MESSAGE));
}

void		Packet_v1_Channel::setChannelName(char const * name)
{
  assert(getRequestId() == CHANNEL_JOIN ||
	 getRequestId() == CHANNEL_JOIN_OK ||
	 getRequestId() == CHANNEL_JOIN_NOK_ALREADYINCHAN ||
         getRequestId() == CHANNEL_JOINED ||
         getRequestId() == CHANNEL_LEAVED ||
	 getRequestId() == CHANNEL_LEAVE_OK);
  appendData(PROTOV1_CHANNEL_START_OF_DATA, PROTOV1_CHANNEL_DATA_CHANNEL_NAME, reinterpret_cast<byte_t const *>(name));
}

char const	*Packet_v1_Channel::getChannelName() const
{
  assert(getRequestId() == CHANNEL_JOIN ||
	 getRequestId() == CHANNEL_JOIN_OK ||
         getRequestId() == CHANNEL_JOIN_NOK_ALREADYINCHAN ||
         getRequestId() == CHANNEL_JOINED ||
         getRequestId() == CHANNEL_LEAVED ||
         getRequestId() == CHANNEL_LEAVE_OK);
  return reinterpret_cast<char const *>(getData(PROTOV1_CHANNEL_START_OF_DATA, PROTOV1_CHANNEL_DATA_CHANNEL_NAME));
}

void		Packet_v1_Channel::setChannelList(std::map<unsigned int, Channel*> *m_channel)
{
  Channel		*chan;
  std::string		name = "";

  std::map<unsigned int, Channel*>::iterator it, end = m_channel->end();
  for (it = m_channel->begin(); it != end; ++it)
    {
      chan = it->second;
      name += chan->getName();
      name += '#';
    }
  appendData(PROTOV1_CHANNEL_START_OF_DATA, PROTOV1_CHANNEL_DATA_CHANNEL_LIST, reinterpret_cast<byte_t const *>(name.c_str()));
}

std::vector<std::string> 	Packet_v1_Channel::getChannelList() const
{
  const std::string& cl = reinterpret_cast<char *>(getData(PROTOV1_CHANNEL_START_OF_DATA, PROTOV1_CHANNEL_DATA_CHANNEL_LIST));
  std::vector<std::string> v;
  size_t begin, sharp = 0;

  for (begin = 0; (sharp = cl.find_first_of('#', begin)) != std::string::npos; begin = sharp +1 )
    v.push_back(cl.substr(begin, sharp - begin));
  return v;
}

void		Packet_v1_Channel::setClientLogin(char const *login)
{
  assert(getRequestId() == CHANNEL_JOINED ||
	 getRequestId() == CHANNEL_LEAVED);
  appendData(PROTOV1_CHANNEL_START_OF_DATA, PROTOV1_CHANNEL_DATA_LOGIN, reinterpret_cast<byte_t const *>(login));
}

char const	*Packet_v1_Channel::getClientLogin() const
{
  assert(getRequestId() == CHANNEL_JOINED ||
	 getRequestId() == CHANNEL_LEAVED);
  return reinterpret_cast<char const *>(getData(PROTOV1_CHANNEL_START_OF_DATA, PROTOV1_CHANNEL_DATA_LOGIN));
}
