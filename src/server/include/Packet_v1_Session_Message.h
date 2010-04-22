#ifndef __PACKET_V1_SESSION_MESSAGE_H__
#define __PACKET_V1_SESSION_MESSAGE_H__

// NOT USED CUZ NO DATA SO YOU CAN USE PACKET_v1 DIRECTLY

#include <iostream>
#include <boost/asio.hpp>

#include <Packet.h>

class Packet_v1_Session_Message : public Packet_v1
{
public:
  Packet_v1_Session_Message(boost::asio::ip::udp::endpoint *);
  virtual ~Packet_v1_Session_Message();

  char const	*getLogin() const;
  char const	*getPass() const;
  void		setLogin(char const *);
  void		setPass(char const *);

private:
};

#endif // ! __PACKET_V1_SESSION_AUTHREQUEST_H__
