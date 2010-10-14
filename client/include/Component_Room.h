#ifndef __COMPONENT_ROOM_H__
#define __COMPONENT_ROOM_H__

class Component_Room;

#include <iostream>
#include <IComponent.h>
#include <Packet_v1.h>
#include <Packet_v1_Room.h>
#include <ClientManager.h>
#include <Protocol.h>
#include <Protocol_Room.h>
#include <Session.h>
#include <Room.h>

//! CLIENT: It is used to manage client interaction with rooms.

class Component_Room : public IComponent
{
public:

  Component_Room(ClientManager *);
  virtual				~Component_Room();

  virtual void				BindingsRecv();
  virtual void				RegisteredRequests();

 public :

  typedef std::map<field_t, Room *>	m_room;

  void					Send_Join(Session *, char * const);
  void					Send_Leave(Session *, field_t);

  void					Send_Message(Session *, char const *, field_t);

  void					Send_Invite(Session *, char const *, field_t );
  void					Send_Kick(Session *, field_t clientSessionId, field_t );

  void					Send_Start_Jam(Session *, field_t );
  void					Send_Stop_Jam(Session *, field_t );

  void					Connect(Session *);
  void					Disconnect(Session *);

private:

  void					Recv_Join_OK(Packet_v1 const *, Session *);
  void					Recv_Join_NOK_ALREADYINROOM(Packet_v1 const *, Session *);

  void					Recv_Joined(Packet_v1 const *, Session *);
  void					Send_Joined_ACK(Session *);

  void					Recv_Message_RECV(Packet_v1 const *, Session *);
  void					Send_Message_RECV_ACK(Session *);

  void					Recv_Leave_OK(Packet_v1 const *, Session *);
  void					Recv_Leave_NOK_NOTINROOM(Packet_v1 const *, Session *);
  
  void					Recv_Leaved(Packet_v1 const *, Session *);
  void					Send_Leaved_ACK(Session *);

  void					Send_Kicked_ACK(Session *);
  void					Send_Invited_ACK(Session *);

  void					Send_Started_Jam_ACK(Session *);
  void					Send_Stoped_Jam_ACK(Session *);

  void					Send_User_Kicked_ACK(Session *);

  void					Recv_Kick_OK(Packet_v1 const *packet_v1, Session *);
  void					Recv_Kick_NOK_NOTINROOM(Packet_v1 const *packet_v1, Session *);

  void					Recv_Invited(Packet_v1 const *packet_v1, Session *);
  void					Recv_User_Kicked(Packet_v1 const *packet_v1, Session *);

  void					Recv_Started_Jam(Packet_v1 const *packet_v1, Session *);
  void					Recv_Stoped_Jam(Packet_v1 const *packet_v1, Session *);

  void					Recv_Kicked(Packet_v1 const *packet_v1, Session *);
 
 private :
  
  ClientManager				*_clientManager;
  m_room				_roomMap;
};

#endif // ! __COMPONENT_ROOM_H__
