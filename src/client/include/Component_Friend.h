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

  void			Send_Friend_Add(Session *, char const *);
  void			Send_Friend_Del(Session *, char const *);

  bool			IsFriend(Session *, std::string const &) const;

 private :
  void			Recv_Friend_Leaved(Packet_v1 const *, Session *);
  void			Recv_Friend_Joined(Packet_v1 const *, Session *);

  void			Recv_Friend_Add_OK(Packet_v1 const *, Session *);
  void			Recv_Friend_Add_NOK(Packet_v1 const *, Session *);

  void			Recv_Friend_Del_OK(Packet_v1 const *, Session *);
  void			Recv_Friend_Del_NOK(Packet_v1 const *, Session *);

  void			Send_Friend_Joined_ACK(Session *);
  void			Send_Friend_Leaved_ACK(Session *);

  void			Connect(Session *);
  void			Disconnect(Session *);

 private :
  ClientManager		*_clientManager;
};

#endif // ! __COMPONENT_FRIEND_H__
