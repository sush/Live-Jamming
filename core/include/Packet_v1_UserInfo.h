#ifndef __PACKET_V1_USERINFO_H__
#define __PACKET_V1_USERINFO_H__

#include <Packet_v1.h>
#include <Protocol.h>
#include <Protocol_UserInfo.h>
#include <Manager.h>

class Packet_v1_UserInfo : public Packet_v1
{

 public :

  Packet_v1_UserInfo(boost::asio::ip::udp::endpoint const *, buffer_t *, std::size_t);
  Packet_v1_UserInfo(field_t);
  virtual			~Packet_v1_UserInfo();
  virtual void			Print(std::string const &, Manager const *) const;

  field_t			getClientSessionId() const;
  void				setClientSessionId(field_t);

  void				setUserInfo(m_userinfo const *);
  m_userinfo const		*getUserInfo() const;

  void				setAvatar(char const *);
  char const		        *getAvatar() const;

protected :
  void				Print_v1_UserInfo(std::string const &, Manager const *) const;

};

#endif // ! __PACKET_V1_FRIEND_H__
