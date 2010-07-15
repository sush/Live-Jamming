#ifndef __COMPONENT_ROOMMANAGER_H__
#define __COMPONENT_ROOMMANAGER_H__

#include <map>
#include <Server.h>
#include <IComponent.h>
#include <Protocol.h>
#include <Protocol_Room.h>
#include <Packet_v1.h>
#include <Packet_v1_Room.h>
#include <ServerManager.h>
#include <Session.h>
#include <Room.h>

//! SERVER:  It is used to manage all rooms.

class Component_RoomManager : public IComponent
{
  friend class Session;
  friend class ServerManager;

public:

  Component_RoomManager(ServerManager *);
  virtual		~Component_RoomManager();

private:

  virtual void		BindingsRecv();
  virtual void		RegisteredRequests();

  void			Recv_Join(Packet_v1 const *, Session *);
  void			Send_Join_OK(Session *, field_t);
  void			Send_Join_NOK_ALREADYINROOM(Session *, field_t, char const *);
  void			Send_Joined(Session *, field_t, field_t, char const *);

  void			Recv_Leave(Packet_v1 const *, Session *);
  void			Send_Leave_OK(Session *, field_t);
  void			Send_Leave_NOK_NOTINROOM(Session *, field_t);
  void			Send_Leaved(Session *, field_t);

  void			Recv_Message(Packet_v1 const *, Session *);
  void			Send_Message_RECV(Session *, char const *, field_t, field_t);
  void			Send_Message_ACK(Session *);

  void			Recv_Kick(Packet_v1 const *, Session *);
  void			Send_Kicked(Session *, field_t);
  void			Send_Kick_OK(Session *, field_t);
  void			Send_Kick_NOK_NOTINROOM(Session *, field_t);

  void			Send_User_Kicked(Session *, field_t);

  void			Recv_Invite(Packet_v1 const *, Session *);
  void			Send_Invite_ACK(Session *);
  void			Send_Invited(Session *, char const *);

  void			Recv_Start_Jam(Packet_v1 const *, Session *);
  void			Send_Started_Jam(Session *);
  void			Send_Start_Jam_ACK(Session *);

  void			Recv_Stop_Jam(Packet_v1 const *, Session *);
  void			Send_Stoped_Jam(Session *);
  void			Send_Stop_Jam_ACK(Session *);

  void			Connect(Session *);
  void			Disconnect(Session *);

  field_t		GenRoomId();
  bool			IsUniqId(field_t) const;

 private :

  ServerManager			*_serverManager;
  typedef std::map<field_t, Room*> m_room;
  m_room			*_roomMap;
  boost::rand48			_rng;
  ServerManager::m_Session      &_sessionMap;
};

#endif // ! __COMPONENT_ROOMMANAGER_H__
