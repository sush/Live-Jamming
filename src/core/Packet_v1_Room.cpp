#include <Packet_v1_Room.h>

Packet_v1_Room::Packet_v1_Room(boost::asio::ip::udp::endpoint const *endpoint, buffer_t *buffer, std::size_t len)
  :Packet_v1::Packet_v1(endpoint, buffer, len)
{}

Packet_v1_Room::Packet_v1_Room(field_t requestId)
  : Packet_v1(ROOM_COMPONENTID, requestId)
{}

Packet_v1_Room::~Packet_v1_Room()
{}

void            Packet_v1_Room::Print(std::string const &componentName, Manager const * manager) const
{
  std::cout << PACKET_STRING << " [Packet_v1_Room] " << PACKET_STRING << std::endl;
  Print_v1_Room(componentName, manager);
  std::cout << PACKET_STRING << PACKET_STRING << PACKET_STRING << std::endl;
}

void            Packet_v1_Room::Print_v1_Room(std::string const &componentName, Manager const * manager) const
{
  Print_v1(componentName, manager);
  std::cout << "[ROOMID: " << getRoomId() << " {" << PROTOV1_ROOM_ROOMID_SIZE << "}]"
	    << "[CLIENTSESSIONID: " << getClientSessionId() << "{" << PROTOV1_ROOM_CLIENTSESSIONID_SIZE << "}]"
	    << std::endl;
  int id = getRequestId();
  if (id == ROOM_JOINED || id == ROOM_LEAVED || id == ROOM_KICKED || ROOM_INVITE)
    std::cout << "# Login: '" << getClientLogin() << "'" << std::endl;
}

field_t         Packet_v1_Room::getRoomId() const
{
  return getField(PROTOV1_ROOM_ROOMID_OFF, PROTOV1_ROOM_ROOMID_SIZE);
}

field_t         Packet_v1_Room::getClientSessionId() const
{
  return getField(PROTOV1_ROOM_CLIENTSESSIONID_OFF, PROTOV1_ROOM_CLIENTSESSIONID_SIZE);
}

void            Packet_v1_Room::setRoomId(field_t roomId)
{
  setField(roomId, PROTOV1_ROOM_ROOMID_OFF, PROTOV1_ROOM_ROOMID_SIZE);
}

void            Packet_v1_Room::setClientSessionId(field_t clientSessionId)
{
  setField(clientSessionId, PROTOV1_ROOM_CLIENTSESSIONID_OFF, PROTOV1_ROOM_CLIENTSESSIONID_SIZE);
}

void            Packet_v1_Room::setMessage(char const * message)
{
  //  assert(getRequestId() == CHANNEL_MESSAGE || getRequestId() == CHANNEL_MESSAGE_RECV);
  appendData(PROTOV1_ROOM_START_OF_DATA, PROTOV1_ROOM_DATA_MESSAGE, reinterpret_cast<byte_t const *>(message));
}

char const      *Packet_v1_Room::getMessage() const
{
  //  assert(getRequestId() == CHANNEL_MESSAGE || getRequestId() == CHANNEL_MESSAGE_RECV);
  return reinterpret_cast<char const *>(getData(PROTOV1_ROOM_START_OF_DATA, PROTOV1_ROOM_DATA_MESSAGE));
}

void            Packet_v1_Room::setRoomName(char const * name)
{
  //  assert(getRequestId() == CHANNEL_JOIN );
  appendData(PROTOV1_ROOM_START_OF_DATA, PROTOV1_ROOM_DATA_ROOM_NAME, reinterpret_cast<byte_t const *>(name));
}

char const      *Packet_v1_Room::getRoomName() const
{
  //  assert(getRequestId() == CHANNEL_JOIN);
  return reinterpret_cast<char const *>(getData(PROTOV1_ROOM_START_OF_DATA, PROTOV1_ROOM_DATA_ROOM_NAME));
}

void            Packet_v1_Room::setClientLogin(char const *login)
{
  //  assert(getRequestId() == CHANNEL_JOINED_);
  appendData(PROTOV1_ROOM_START_OF_DATA, PROTOV1_ROOM_DATA_LOGIN, reinterpret_cast<byte_t const *>(login));
}

char const      *Packet_v1_Room::getClientLogin() const
{
  //  assert(getRequestId() == CHANNEL_JOINED);
  return reinterpret_cast<char const *>(getData(PROTOV1_ROOM_START_OF_DATA, PROTOV1_ROOM_DATA_LOGIN));
}

