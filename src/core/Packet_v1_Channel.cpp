#include <Packet_v1_Channel.h>

Packet_v1_Channel::Packet_v1_Channel(field_t requestId)
  : Packet_v1(CHANNEL_COMPONENTID, requestId)
{}

Packet_v1_Channel::~Packet_v1_Channel()
{}

void		Packet_v1_Channel::Print() const
{
  // problem with dynamic_cast from Packet* to Packet_v1_Channel*
  // wrong function is called so Print_v1 was created
  //  Print_v1();  
}

void		Packet_v1_Channel::Print_v1() const
{
  std::cout << "[PROTO_VERSION: " << getProtoVersion() << " {" << PROTO_PROTOVERSION_SIZE << "}]"
	    << "[COMPONENTID: " << getComponentId() << " {" << PROTOV1_COMPONENTID_SIZE << "}]"
	    << "[REQUESTID: " << getRequestId() << " {" << PROTOV1_REQUESTID_SIZE << "}]"
	    << "[SESSIONID: " << getSessionId() << " {" << PROTOV1_SESSIONID_SIZE << "}]"
	    << "[DATALEN: " << getDataLen() << " {" << PROTOV1_DATALEN_SIZE << "}]"
	    << std::endl;
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
	 getRequestId() == CHANNEL_JOIN_NOK_ALREADY_IN_CHAN);
  appendData(PROTOV1_CHANNEL_START_OF_DATA, PROTOV1_CHANNEL_DATA_CHANNEL_NAME, reinterpret_cast<byte_t const *>(name));
}

char const	*Packet_v1_Channel::getChannelName() const
{
  assert(getRequestId() == CHANNEL_JOIN ||
	 getRequestId() == CHANNEL_JOIN_OK ||
	 getRequestId() == CHANNEL_JOIN_NOK_ALREADY_IN_CHAN);
  return reinterpret_cast<char const *>(getData(PROTOV1_CHANNEL_START_OF_DATA, PROTOV1_CHANNEL_DATA_CHANNEL_NAME));
}
