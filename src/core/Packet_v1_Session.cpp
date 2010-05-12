#include <Packet_v1_Session.h>

Packet_v1_Session::Packet_v1_Session(field_t requestId)
  : Packet_v1(SESSION_COMPONENTID, requestId)
{}

Packet_v1_Session::~Packet_v1_Session()
{}

byte_t const	*Packet_v1_Session::getLogin() const
{
  assert(getRequestId() == SESSION_AUTHREQUEST);
  return (byte_t const *) "login";
}

byte_t const	*Packet_v1_Session::getPass() const
{
  assert(getRequestId() == SESSION_AUTHREQUEST);
  return (byte_t const *) "pass";
}

void		Packet_v1_Session::setLogin(char const *login)
{
  assert(getRequestId() == SESSION_AUTHREQUEST);
  login = login;
}

void		Packet_v1_Session::setPass(char const *pass)
{
  assert(getRequestId() == SESSION_AUTHREQUEST);
  pass = pass;
}

