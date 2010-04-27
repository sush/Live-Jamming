#ifndef __PACKET_V1_SESSION_AUTHREQUEST_H__
#define __PACKET_V1_SESSION_AUTHREQUEST_H__

#include <iostream>
#include <boost/asio.hpp>

#include <Packet_v1.h>
#include <Protocol.h>

class Packet_v1_Session_AuthRequest : public Packet_v1
{
public:
  Packet_v1_Session_AuthRequest(boost::asio::ip::udp::endpoint *);
  virtual ~Packet_v1_Session_AuthRequest();

  byte_t const	*getLogin() const;
  byte_t const	*getPass() const;
  void		setLogin(char const *);
  void		setPass(char const *);

private:
  byte_t	*_login;
  byte_t	*_pass;
};

#endif // ! __PACKET_V1_SESSION_AUTHREQUEST_H__
