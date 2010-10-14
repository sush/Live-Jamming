#ifndef __PACKET_V1_FRIEND_H__
#define __PACKET_V1_FRIEND_H__

class Manager;

#include <Packet_v1.h>
#include <Protocol.h>
#include <Protocol_Friend.h>

class Packet_v1_Friend : public Packet_v1
{

 public :

  Packet_v1_Friend(boost::asio::ip::udp::endpoint const *, buffer_t *, std::size_t);
  Packet_v1_Friend(field_t);
  virtual			~Packet_v1_Friend();
  virtual void					Print(std::string const &, Manager const *) const;

  char const			*getFriendLogin() const;
  void				setFriendLogin(char const *);

protected :
  void				Print_v1_Friend(std::string const &, Manager const *) const;

};

#endif // ! __PACKET_V1_FRIEND_H__
