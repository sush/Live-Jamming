
#include <Packet_v1_Jam.h>
#include <cmath>

Packet_v1_Jam::Packet_v1_Jam(boost::asio::ip::udp::endpoint const *endpoint, buffer_t *buffer, std::size_t len)
  :Packet_v1::Packet_v1(endpoint, buffer, len)
{}

Packet_v1_Jam::Packet_v1_Jam(field_t requestId)
  : Packet_v1(JAM_COMPONENTID, requestId)
{}

Packet_v1_Jam::~Packet_v1_Jam()
{}

void            Packet_v1_Jam::Print(std::string const &componentName, Manager const * manager) const
{
  std::cout << PACKET_STRING << " [Packet_v1_Jam] " << PACKET_STRING << std::endl;
  Print_v1_Jam(componentName, manager);
  std::cout << PACKET_STRING << PACKET_STRING << PACKET_STRING << std::endl;
}

void            Packet_v1_Jam::Print_v1_Jam(std::string const &componentName, Manager const * manager) const
{
  Print_v1(componentName, manager);
}

field_t         Packet_v1_Jam::getJamId() const
{
  return getField(PROTOV1_JAM_JAMID_OFF, PROTOV1_JAM_JAMID_SIZE);
}

void            Packet_v1_Jam::setJamId(field_t jamId)
{
  setField(jamId, PROTOV1_JAM_JAMID_OFF, PROTOV1_JAM_JAMID_SIZE);
}

void            Packet_v1_Jam::setClientSessionId(field_t clientSessionId)
{
  setField(clientSessionId, PROTOV1_JAM_CLIENTSESSIONID_OFF, PROTOV1_JAM_CLIENTSESSIONID_SIZE);
}

field_t         Packet_v1_Jam::getClientSessionId() const
{
  return getField(PROTOV1_JAM_CLIENTSESSIONID_OFF, PROTOV1_JAM_CLIENTSESSIONID_SIZE);
}

void            Packet_v1_Jam::setAudioDataLen(field_t audioDataLen)
{
  setField(audioDataLen, PROTOV1_JAM_AUDIODATALEN_OFF, PROTOV1_JAM_AUDIODATALEN_SIZE);
}

field_t         Packet_v1_Jam::getAudioDataLen() const
{
  return getField(PROTOV1_JAM_AUDIODATALEN_OFF, PROTOV1_JAM_AUDIODATALEN_SIZE);
}

void            Packet_v1_Jam::setAudio(byte_t const * audio, field_t len)
{
  byte_t	*res;

  assert(len < PACKET_MAXSIZE - 50); // taille fixe pour le moment...

  setAudioDataLen(len);
  res = getStartOfData(PROTOV1_JAM_START_OF_DATA, PROTOV1_JAM_DATA_AUDIO);
  // assert(getRequestId() == CHANNEL_MESSAGE || getRequestId() == CHANNEL_MESSAGE_RECV);
  for (unsigned int i = 0; i < len; ++i)
    res[i] = audio[i];
}

byte_t const      *Packet_v1_Jam::getAudio(field_t len) const
{
  //  assert(getRequestId() == CHANNEL_MESSAGE || getRequestId() == CHANNEL_MESSAGE_RECV);                            

  return getStartOfData(PROTOV1_JAM_START_OF_DATA, PROTOV1_JAM_DATA_AUDIO);
}

void            Packet_v1_Jam::setMixCount(field_t mixcount)
{
  setField(clientSessionId, PROTOV1_JAM_CLIENTSESSIONID_OFF, PROTOV1_JAM_CLIENTSESSIONID_SIZE);
}

field_t         Packet_v1_Jam::getMixCount() const
{
  return getField(PROTOV1_JAM_MIXCOUNT_OFF, PROTOV1_JAM_MIXCOUNT_SIZE);
}
