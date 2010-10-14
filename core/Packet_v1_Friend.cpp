#include <Packet_v1_Friend.h>

Packet_v1_Friend::Packet_v1_Friend(boost::asio::ip::udp::endpoint const *endpoint, buffer_t *buffer, std::size_t len)
  :Packet_v1::Packet_v1(endpoint, buffer, len)
{}


Packet_v1_Friend::Packet_v1_Friend(field_t requestId)
  : Packet_v1(FRIEND_COMPONENTID, requestId)
{}

Packet_v1_Friend::~Packet_v1_Friend()
{}

void	Packet_v1_Friend::Print(std::string const &componentName, Manager const * manager) const
{
  std::cout << PACKET_STRING << " [Packet_v1_Friend] " << PACKET_STRING << std::endl;
  Print_v1_Friend(componentName, manager);
  std::cout << PACKET_STRING << PACKET_STRING << PACKET_STRING << std::endl;
}

void		Packet_v1_Friend::Print_v1_Friend(std::string const &componentName, Manager const * manager) const
{
  Print_v1(componentName, manager);
  int id = getRequestId();
  if (id == FRIEND_JOINED || id == FRIEND_LEAVED || id == FRIEND_ADD || id == FRIEND_DEL)
    std::cout << "# Login: '" << getFriendLogin() << "'" << std::endl;
}

void		Packet_v1_Friend::setFriendLogin(char const * friendLogin)
{
  assert(getRequestId() == FRIEND_JOINED || 
	 getRequestId() == FRIEND_LEAVED || 
	 getRequestId() == FRIEND_ADD_OK ||
	 getRequestId() == FRIEND_ADD_NOK ||
	 getRequestId() == FRIEND_DEL_OK ||
	 getRequestId() == FRIEND_DEL_NOK);

  appendData(PROTOV1_FRIEND_START_OF_DATA, PROTOV1_FRIEND_DATA_LOGIN, reinterpret_cast<byte_t const *>(friendLogin));
}
char const	*Packet_v1_Friend::getFriendLogin() const
{
  assert(getRequestId() == FRIEND_JOINED || 
	 getRequestId() == FRIEND_LEAVED || 
	 getRequestId() == FRIEND_ADD_OK ||
	 getRequestId() == FRIEND_ADD_NOK ||
	 getRequestId() == FRIEND_DEL_OK ||
	 getRequestId() == FRIEND_DEL_NOK);

  return reinterpret_cast<char const *>(getData(PROTOV1_FRIEND_START_OF_DATA, PROTOV1_FRIEND_DATA_LOGIN));
}
