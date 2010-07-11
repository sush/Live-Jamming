#ifndef __PACKET_V1_SESSION_H__
#define __PACKET_V1_SESSION_H__

#include <iostream>
#include <boost/asio.hpp>

#include <Packet_v1.h>
#include <Protocol.h>
#include <Protocol_Session.h>

class Packet_v1_Session : public Packet_v1
{
public:
  Packet_v1_Session(field_t);
  virtual ~Packet_v1_Session();

  char const	*getLogin() const;
  char const	*getPass() const;
  char const	*getFriendLogin() const;

  void		setLogin(char const *);
  void		setPass(char const *);
  void		setFriendLogin(char const *);

};

#endif // ! __PACKET_V1_SESSION_H__
