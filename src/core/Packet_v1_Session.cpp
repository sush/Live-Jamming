#include <Packet_v1_Session.h>

Packet_v1_Session::Packet_v1_Session(field_t requestId)
  : Packet_v1(SESSION_COMPONENTID, requestId)
{}

Packet_v1_Session::~Packet_v1_Session()
{}

char const	*Packet_v1_Session::getLogin() const
{
  assert(getRequestId() == SESSION_AUTHREQUEST);
  return reinterpret_cast<char const *>(getData(PROTOV1_SESSION_START_OF_DATA, PROTOV1_SESSION_DATA_LOGIN));
}

char const	*Packet_v1_Session::getPass() const
{
  assert(getRequestId() == SESSION_AUTHREQUEST);
  return reinterpret_cast<char const *>(getData(PROTOV1_SESSION_START_OF_DATA, PROTOV1_SESSION_DATA_PASS));
}

void		Packet_v1_Session::setLogin(char const *login)
{
  assert(getRequestId() == SESSION_AUTHREQUEST);
  appendData(PROTOV1_SESSION_START_OF_DATA, PROTOV1_SESSION_DATA_LOGIN, reinterpret_cast<byte_t const *>(login));
}

void		Packet_v1_Session::setPass(char const *pass)
{
  assert(getRequestId() == SESSION_AUTHREQUEST);
  appendData(PROTOV1_SESSION_START_OF_DATA, PROTOV1_SESSION_DATA_PASS, reinterpret_cast<byte_t const *>(pass));
}

void		Packet_v1_Session::setFriendLogin(char const * friendLogin)
{
  assert(getRequestId() == SESSION_AUTHREQUEST || SESSION_ADD_FRIEND || SESSION_DEL_FRIEND || SESSION_ADD_FRIEND_OK || SESSION_ADD_FRIEND_NOK || SESSION_DEL_FRIEND_OK || SESSION_DEL_FRIEND_NOK);
  appendData(PROTOV1_SESSION_START_OF_DATA, PROTOV1_SESSION_DATA_FRIEND, reinterpret_cast<byte_t const *>(friendLogin));
}

char const	*Packet_v1_Session::getFriendLogin() const
{
  assert(getRequestId() == SESSION_FRIEND_JOINED || SESSION_FRIEND_LEAVED || SESSION_ADD_FRIEND_OK || SESSION_ADD_FRIEND_NOK || SESSION_DEL_FRIEND_OK || SESSION_DEL_FRIEND_NOK);
  return reinterpret_cast<char const *>(getData(PROTOV1_SESSION_START_OF_DATA, PROTOV1_SESSION_DATA_FRIEND));
}
