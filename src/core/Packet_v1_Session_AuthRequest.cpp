#include <Packet_v1_Session_AuthRequest.h>

Packet_v1_Session_AuthRequest::Packet_v1_Session_AuthRequest(boost::asio::ip::udp::endpoint const *endpoint)
  : Packet_v1(endpoint), _login(0), _pass(0)
{
  setType(SESSION_AUTH_REQUEST);
}

Packet_v1_Session_AuthRequest::~Packet_v1_Session_AuthRequest()
{
}

Packet::byte_t const	*Packet_v1_Session_AuthRequest::getLogin() const
{
  return (byte_t const *) "login";

  int			i;

  for (i = 0; i < PACKET_MAXSIZE && _buffer->at(PROTOV1_START_OF_DATA / 8 + i) != '\0'; ++i);
  if (i == 0 || i == PACKET_MAXSIZE)
    return 0;
  return &_buffer->at(PROTOV1_START_OF_DATA / 8);
}

Packet::byte_t const	*Packet_v1_Session_AuthRequest::getPass() const
{
  // just to test
  return (byte_t const *) "pass";
}

void		Packet_v1_Session_AuthRequest::setLogin(char const *login)
{
  login = login;
//   _buffer->at(PROTOV1_START_OF_DATA / 8) = 'o';
//   _buffer->at(PROTOV1_START_OF_DATA / 8 + 1) = '-';
//   _buffer->at(PROTOV1_START_OF_DATA / 8 + 2) = 'c';
//   _buffer->at(PROTOV1_START_OF_DATA / 8 + 3) = 'o';
//   _buffer->at(PROTOV1_START_OF_DATA / 8 + 4) = 'n';
//   _buffer->at(PROTOV1_START_OF_DATA / 8 + 5) = 'n';
//   _buffer->at(PROTOV1_START_OF_DATA / 8 + 6) = '_';
//   _buffer->at(PROTOV1_START_OF_DATA / 8 + 7) = 'g';
//   _buffer->at(PROTOV1_START_OF_DATA / 8 + 8) = '\0';
}

void		Packet_v1_Session_AuthRequest::setPass(char const *pass)
{
  pass = pass;
}

