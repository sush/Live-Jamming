#ifndef __COMPONENT_FRIEND_H__
#define __COMPONENT_FRIEND_H__

class Component_Friend;

#include <IComponent.h>
#include <Packet_v1.h>
#include <Packet_v1_Friend.h>
#include <ClientManager.h>
#include <Protocol.h>
#include <Protocol_Friend.h>
#include <Session.h>

class Component_Friend :public IComponent
{
 public :
  Component_Friend(ClientManager*);
  virtual		~Component_Friend();

  virtual void		BindingsRecv();
  virtual void		RegisteredRequests();

  void			Send_Friend_Add(char const *);
  void			Send_Friend_Del(char const *);

  bool			IsFriend(std::string const &) const;

 private :
  void			Recv_Friend_Leaved(Packet_v1 const *, Session *);
  void			Recv_Friend_Joined(Packet_v1 const *, Session *);

  void			Recv_Friend_Add_OK(Packet_v1 const *, Session *);
  void			Recv_Friend_Add_NOK(Packet_v1 const *, Session *);

  void			Recv_Friend_Del_OK(Packet_v1 const *, Session *);
  void			Recv_Friend_Del_NOK(Packet_v1 const *, Session *);

  void			Recv_Friend_List(Packet_v1 const *, Session *);

 private :
  ClientManager				*_clientManager;
  typedef std::vector<std::string>	v_friend;
  v_friend				*_friendList;

};

#endif // ! __COMPONENT_FRIEND_H__
