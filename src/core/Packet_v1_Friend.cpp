#include <Packet_v1_Friend.h>

Packet_v1_Friend::Packet_v1_Friend(field_t requestId)
  : Packet_v1(FRIEND_COMPONENTID, requestId)
{}

Packet_v1_Friend::~Packet_v1_Friend()
{}

void		Packet_v1_Friend::Print_v1() const
{
  std::cout << "[PROTO_VERSION: " << getProtoVersion() << " {" << PROTO_PROTOVERSION_SIZE << "}]"
	    << "[COMPONENTID: " << getComponentId() << " {" << PROTOV1_COMPONENTID_SIZE << "}]"
	    << "[REQUESTID: " << getRequestId() << " {" << PROTOV1_REQUESTID_SIZE << "}]"
	    << "[SESSIONID: " << getSessionId() << " {" << PROTOV1_SESSIONID_SIZE << "}]"
	    << "[DATALEN: " << getDataLen() << " {" << PROTOV1_DATALEN_SIZE << "}]"
	    << std::endl;
}

void		Packet_v1_Friend::setFriendLogin(char const * friendLogin)
{
  // assert(getRequestId() == SESSION_AUTHREQUEST || SESSION_ADD_FRIEND || SESSION_DEL_FRIEND 
  // 	 || SESSION_ADD_FRIEND_OK || SESSION_ADD_FRIEND_NOK || SESSION_DEL_FRIEND_OK || SESSION_DEL_FRIEND_NOK);

  appendData(PROTOV1_FRIEND_START_OF_DATA, PROTOV1_FRIEND_DATA_LOGIN, reinterpret_cast<byte_t const *>(friendLogin));
}
char const	*Packet_v1_Friend::getFriendLogin() const
{
  // assert(getRequestId() == SESSION_FRIEND_JOINED || SESSION_FRIEND_LEAVED || SESSION_ADD_FRIEND_OK 
  // 	 || SESSION_ADD_FRIEND_NOK || SESSION_DEL_FRIEND_OK || SESSION_DEL_FRIEND_NOK);

  return reinterpret_cast<char const *>(getData(PROTOV1_FRIEND_START_OF_DATA, PROTOV1_FRIEND_DATA_LOGIN));
}

void		Packet_v1_Friend::setFriendList(std::vector<std::string> const &friendList)
{
  std::string           friends;

  for (unsigned int i = 0; i < friendList.size(); ++i)
    {
      friends += friendList[i];
      friends += "#";
    }
  appendData(PROTOV1_FRIEND_START_OF_DATA, PROTOV1_FRIEND_DATA_LIST, reinterpret_cast<byte_t const *>(friends.c_str()));
}

std::vector<std::string>	*Packet_v1_Friend::getFriendList() const
{
  char const                    *friendList = reinterpret_cast<char const *>(getData(PROTOV1_FRIEND_START_OF_DATA, PROTOV1_FRIEND_DATA_LIST));

  std::vector<std::string>      *v_friend = new std::vector<std::string>();
  std::string                   name;

  for (unsigned int i = 0; i < strlen(friendList); ++i)
    {
      if (friendList[i] == '\0')
        break;
      if (friendList[i] != '#')
        name += friendList[i];
      else
        {
          v_friend->push_back(name);
          name.clear();
        }
    }
  return v_friend;
}
