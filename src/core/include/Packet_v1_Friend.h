#ifndef __PACKET_V1_FRIEND_H__
#define __PACKET_V1_FRIEND_H__

#include <Packet_v1.h>
#include <Protocol.h>
#include <Protocol_Friend.h>

class Packet_v1_Friend : public Packet_v1
{

 public :

  Packet_v1_Friend(field_t);
  virtual			~Packet_v1_Friend();

  void				Print_v1() const;

  char const			*getFriendLogin() const;
  std::vector<std::string>	*getFriendList() const;


  void				setFriendLogin(char const *);
  void				setFriendList(std::vector<std::string> const &);

 private :

};

#endif // ! __PACKET_V1_FRIEND_H__
