#include <Packet_v1_UserInfo.h>
#include <Tools.h>
#include <assert.h>
#include <Protocol_UserInfo.h>

Packet_v1_UserInfo::Packet_v1_UserInfo(boost::asio::ip::udp::endpoint const *endpoint, buffer_t *buffer, std::size_t len)
  :Packet_v1::Packet_v1(endpoint, buffer, len)
{}

Packet_v1_UserInfo::Packet_v1_UserInfo(field_t requestId)
  : Packet_v1(USERINFO_COMPONENTID, requestId)
{}

Packet_v1_UserInfo::~Packet_v1_UserInfo()
{}

void            Packet_v1_UserInfo::Print(std::string const &componentName, Manager const * manager) const
{
  std::cout << PACKET_STRING << " [Packet_v1_UserInfo] " << PACKET_STRING << std::endl;
  Print_v1_UserInfo(componentName, manager);
  std::cout << PACKET_STRING << PACKET_STRING << PACKET_STRING << std::endl;
}

void            Packet_v1_UserInfo::Print_v1_UserInfo(std::string const &componentName, Manager const * manager) const
{
  Print_v1(componentName, manager);
  std::cout  << "[CLIENTSESSIONID: " << getClientSessionId() << "{" << PROTOV1_USERINFO_CLIENTSESSIONID_SIZE << "}]"
	    << std::endl;
//   int id = getRequestId();
//   if (id == USERINFO_GETINFO_RESPONSE_OK)
//     std::cout << "# UserInfo: '" << getUserInfoName() << "'" << std::endl;
//   if (id == USERINFO_JOINED || id == USERINFO_KICKED || id == USERINFO_INVITE)
//     std::cout << "# Login: '" << getClientLogin() << "'" << std::endl;
//   if (id == USERINFO_MESSAGE || id == USERINFO_MESSAGE_RECV)
//     std::cout << "# Message: '" << getMessage() << "'" << std::endl;
}

field_t         Packet_v1_UserInfo::getClientSessionId() const
{
  return getField(PROTOV1_USERINFO_CLIENTSESSIONID_OFF, PROTOV1_USERINFO_CLIENTSESSIONID_SIZE);
}

void            Packet_v1_UserInfo::setClientSessionId(field_t clientSessionId)
{
  setField(clientSessionId, PROTOV1_USERINFO_CLIENTSESSIONID_OFF, PROTOV1_USERINFO_CLIENTSESSIONID_SIZE);
}

void            Packet_v1_UserInfo::setUserInfo(m_userinfo const *userinfo)
{
  assert(getRequestId() == USERINFO_GETINFO_RESPONSE_OK);
  char const	* serialized = serialize(userinfo);

  appendData(PROTOV1_USERINFO_START_OF_DATA, PROTOV1_USERINFO_DATA_USERINFO, reinterpret_cast<byte_t const *>(serialized));
}

m_userinfo const      *Packet_v1_UserInfo::getUserInfo() const
{
  assert(getRequestId() == USERINFO_GETINFO_RESPONSE_OK);
  m_userinfo const    * unserialized =
    unserialize(reinterpret_cast<char const *>(getData(PROTOV1_USERINFO_START_OF_DATA, PROTOV1_USERINFO_DATA_USERINFO)));
  return unserialized;
}

void            Packet_v1_UserInfo::setAvatar(char const *avatar)
{
  assert(getRequestId() == USERINFO_GETAVATAR_RESPONSE_OK);
  appendData(PROTOV1_USERINFO_START_OF_DATA,
	     PROTOV1_USERINFO_DATA_AVATAR,
	     reinterpret_cast<byte_t const *>(avatar));
}

char const      *Packet_v1_UserInfo::getAvatar() const
{
  assert(getRequestId() == USERINFO_GETAVATAR_RESPONSE_OK);
  return reinterpret_cast<char const *>(getData(PROTOV1_USERINFO_START_OF_DATA, PROTOV1_USERINFO_DATA_AVATAR));
}

