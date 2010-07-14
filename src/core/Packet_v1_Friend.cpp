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

// void		Packet_v1_Friend::setFriendList(std::vector<std::string> const &friendList)
// {
//   std::string           friends;

//   for (unsigned int i = 0; i < friendList.size(); ++i)
//     {
//       friends += friendList[i];
//       friends += "#";
//     }
//   appendData(PROTOV1_FRIEND_START_OF_DATA, PROTOV1_FRIEND_DATA_LIST, reinterpret_cast<byte_t const *>(friends.c_str()));
// }

// std::vector<std::string>	*Packet_v1_Friend::getFriendList() const
// {
//   char const                    *friendList = reinterpret_cast<char const *>(getData(PROTOV1_FRIEND_START_OF_DATA, PROTOV1_FRIEND_DATA_LIST));

//   std::vector<std::string>      *v_friend = new std::vector<std::string>();
//   std::string                   name;

//   for (unsigned int i = 0; i < strlen(friendList); ++i)
//     {
//       if (friendList[i] == '\0')
//         break;
//       if (friendList[i] != '#')
//         name += friendList[i];
//       else
//         {
//           v_friend->push_back(name);
//           name.clear();
//         }
//     }
//   return v_friend;
// }
