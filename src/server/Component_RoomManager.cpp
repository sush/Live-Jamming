#include <Component_RoomManager.h>
#include <Component_JamManager.h>
#include <Bind_recv.h>

Component_RoomManager::Component_RoomManager(ServerManager *serverManager)
  :IComponent(ROOM_COMPONENTID), _serverManager(serverManager), _sessionMap(serverManager->getSessionMap())
{
  _roomMap = new m_room();
}

Component_RoomManager::~Component_RoomManager() 
{}

void	Component_RoomManager::BindingsRecv()
{
   (*_bindingsRecv)[ROOM_JOIN] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_RoomManager::Recv_Join));

  (*_bindingsRecv)[ROOM_JOINED_ACK] =
    new Bind_recv(0, 0);

  (*_bindingsRecv)[ROOM_LEAVE] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_RoomManager::Recv_Leave));

  (*_bindingsRecv)[ROOM_LEAVED_ACK] =
    new Bind_recv(0, 0);

  (*_bindingsRecv)[ROOM_MESSAGE] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_RoomManager::Recv_Message));

  (*_bindingsRecv)[ROOM_MESSAGE_RECV_ACK] =
    new Bind_recv(0, 0);

  (*_bindingsRecv)[ROOM_KICK] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_RoomManager::Recv_Kick));

  (*_bindingsRecv)[ROOM_KICKED_ACK] =
    new Bind_recv(0, 0);

  (*_bindingsRecv)[ROOM_INVITE] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_RoomManager::Recv_Invite));

  (*_bindingsRecv)[ROOM_INVITED_ACK] =
    new Bind_recv(0, 0);

  (*_bindingsRecv)[ROOM_USER_KICKED_ACK] =
    new Bind_recv(0, 0);

  (*_bindingsRecv)[ROOM_START_JAM] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_RoomManager::Recv_Start_Jam));    

  (*_bindingsRecv)[ROOM_STOP_JAM] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_RoomManager::Recv_Stop_Jam));

  (*_bindingsRecv)[ROOM_STARTED_JAM_ACK] =
    new Bind_recv(0, 0);

  (*_bindingsRecv)[ROOM_STOPED_JAM_ACK] =
    new Bind_recv(0, 0);
  //implement Jam methods

}

void	Component_RoomManager::RegisteredRequests()
{
  // SEND requests
  (*_registeredRequests)[ROOM_JOIN_OK] = 
    new Request(ROOM_JOIN_OK, SEND, "JOIN_OK", NORETRY);

  (*_registeredRequests)[ROOM_JOIN_NOK_ALREADYINROOM] = 
    new Request(ROOM_JOIN_NOK_ALREADYINROOM, SEND, "JOIN_NOK_ALREADYINROOM", NORETRY);

  (*_registeredRequests)[ROOM_JOINED] = 
    new Request(ROOM_JOINED, SEND, "JOINED", RETRY);

  (*_registeredRequests)[ROOM_LEAVE_OK] = 
    new Request(ROOM_LEAVE_OK, SEND, "LEAVE_OK", NORETRY);

  (*_registeredRequests)[ROOM_LEAVE_NOK_NOTINROOM] = 
    new Request(ROOM_LEAVE_NOK_NOTINROOM, SEND, "LEAVE_NOK_NOTINROOM", NORETRY);

  (*_registeredRequests)[ROOM_LEAVED] = 
    new Request(ROOM_LEAVED, SEND, "LEAVED", RETRY);

  (*_registeredRequests)[ROOM_MESSAGE_RECV] = 
    new Request(ROOM_MESSAGE_RECV, SEND, "MESSAGE_RECV", RETRY);

  (*_registeredRequests)[ROOM_MESSAGE_ACK] = 
    new Request(ROOM_MESSAGE_ACK, SEND, "MESSAGE_ACK", NORETRY);

  (*_registeredRequests)[ROOM_INVITE_ACK] = 
    new Request(ROOM_INVITE_ACK, SEND, "INVITE_ACK", NORETRY);

  (*_registeredRequests)[ROOM_INVITED] = 
    new Request(ROOM_INVITED, SEND, "INVITED", RETRY);

  (*_registeredRequests)[ROOM_START_JAM_ACK] = 
    new Request(ROOM_START_JAM_ACK, SEND, "START_JAM_ACK", NORETRY);

  (*_registeredRequests)[ROOM_STOP_JAM_ACK] = 
    new Request(ROOM_STOP_JAM_ACK, SEND, "STOP_JAM_ACK", NORETRY);

  (*_registeredRequests)[ROOM_KICKED] = 
    new Request(ROOM_KICKED, SEND, "KICKED", RETRY);

  (*_registeredRequests)[ROOM_USER_KICKED] = 
    new Request(ROOM_USER_KICKED, SEND, "USER_KICKED", RETRY);

  (*_registeredRequests)[ROOM_KICK_OK] = 
    new Request(ROOM_KICK_OK, SEND, "KICK_OK", NORETRY);

  (*_registeredRequests)[ROOM_KICK_NOK_NOTINROOM] = 
    new Request(ROOM_KICK_NOK_NOTINROOM, SEND, "KICK_NON_NOTINROOM", NORETRY);

  (*_registeredRequests)[ROOM_STARTED_JAM] = 
    new Request(ROOM_STARTED_JAM, SEND, "STARTED_JAM", RETRY);

  (*_registeredRequests)[ROOM_STOPED_JAM] = 
    new Request(ROOM_STOPED_JAM, SEND, "STOPED_JAM", RETRY);

  (*_registeredRequests)[ROOM_START_JAM_ACK] = 
    new Request(ROOM_START_JAM_ACK, SEND, "START_JAM_ACK", NORETRY);

  (*_registeredRequests)[ROOM_STOP_JAM_ACK] = 
    new Request(ROOM_STOP_JAM_ACK, SEND, "STOP_JAM_ACK", NORETRY);

  // RECV request
  (*_registeredRequests)[ROOM_JOIN] = 
    new Request(ROOM_JOIN, RECV, "JOIN", RESPONSETONOTHING);

  (*_registeredRequests)[ROOM_JOINED_ACK] = 
    new Request(ROOM_JOINED_ACK, RECV, "JOINED_ACK", ROOM_JOINED);

  (*_registeredRequests)[ROOM_LEAVE] = 
    new Request(ROOM_LEAVE, RECV, "LEAVE", RESPONSETONOTHING);

  (*_registeredRequests)[ROOM_LEAVED_ACK] = 
    new Request(ROOM_LEAVED_ACK, RECV, "JOINED_ACK", ROOM_LEAVED);

  (*_registeredRequests)[ROOM_MESSAGE] = 
    new Request(ROOM_MESSAGE, RECV, "MESSAGE", RESPONSETONOTHING);

  (*_registeredRequests)[ROOM_MESSAGE_RECV_ACK] = 
    new Request(ROOM_MESSAGE_RECV_ACK, RECV, "MESSAGE_RECV_ACK", ROOM_MESSAGE_RECV);

  (*_registeredRequests)[ROOM_KICK] = 
    new Request(ROOM_KICK, RECV, "KICK", RESPONSETONOTHING);

  (*_registeredRequests)[ROOM_KICKED_ACK] = 
    new Request(ROOM_KICKED_ACK, RECV, "KICKED_ACK", ROOM_KICKED);

  (*_registeredRequests)[ROOM_INVITE] = 
    new Request(ROOM_INVITE, RECV, "INVITE", RESPONSETONOTHING);

  (*_registeredRequests)[ROOM_INVITED_ACK] = 
    new Request(ROOM_INVITED_ACK, RECV, "INVITED_ACK", ROOM_INVITED);

  (*_registeredRequests)[ROOM_USER_KICKED_ACK] = 
    new Request(ROOM_USER_KICKED_ACK, RECV, "USER_KICKED_ACK", ROOM_USER_KICKED);

  (*_registeredRequests)[ROOM_START_JAM] = 
    new Request(ROOM_START_JAM, RECV, "START_JAM", RESPONSETONOTHING);

  (*_registeredRequests)[ROOM_STARTED_JAM_ACK] = 
    new Request(ROOM_STARTED_JAM_ACK, RECV, "STARTED_JAM", ROOM_STARTED_JAM);

  (*_registeredRequests)[ROOM_STOP_JAM] = 
    new Request(ROOM_STOP_JAM, RECV, "STOP_JAM", RESPONSETONOTHING);

  (*_registeredRequests)[ROOM_STOPED_JAM] = 
    new Request(ROOM_STOPED_JAM, RECV, "STOPED_JAM", ROOM_STOPED_JAM);
}

void	Component_RoomManager::Recv_Join(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  field_t roomId;
  field_t sessionId		= packet_v1_room->getSessionId();
  char const *roomName		= packet_v1_room->getRoomName();
  Room *room;
  bool existing			= false;

  m_room::iterator it, end = _roomMap->end();
  for (it = _roomMap->begin(); it != end; ++it)
    {
      room = it->second;
      if (strcmp(room->getName(), roomName) == 0)
	{
	  roomId = it->first;
	  existing = true;
	  break;
	}
    }

  if (!existing)
    {
      roomId =  GenRoomId();
      room = new Room(roomName);
      _roomMap->insert(std::pair<field_t, Room*>(roomId, room));
    }

  if (room->addConnected(session, sessionId))
    {
      Send_Join_OK(session, roomId, roomName);

      std::map<field_t, Session*> *connected = room->getConnected();
      std::map<field_t, Session *>::iterator it, end = connected->end();

      for (it = connected->begin(); it != end ; ++it)
	{
	  if (it->first != sessionId)
	    {
	      Send_Joined(session, roomId, it->first, it->second->getLogin().c_str());
	      Send_Joined(it->second, roomId, sessionId, session->getLogin().c_str());
	    }
	}
    }
  else
    Send_Join_NOK_ALREADYINROOM(session, roomId, roomName);
}

void	Component_RoomManager::Send_Join_OK(Session *session, field_t roomId, char const *roomName)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_JOIN_OK);

  packet_v1_room->setRoomName(roomName);
  packet_v1_room->setRoomId(roomId);

  _serverManager->Send(packet_v1_room, session);
}

void	Component_RoomManager::Send_Join_NOK_ALREADYINROOM(Session *session, field_t roomId, char const *roomName)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_JOIN_NOK_ALREADYINROOM);

  packet_v1_room->setRoomId(roomId);
  packet_v1_room->setRoomName(roomName);
  _serverManager->Send(packet_v1_room, session);
}

void	Component_RoomManager::Send_Joined(Session *session, field_t roomId, field_t clientSessionId, char const *clientLogin)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_JOINED);

  packet_v1_room->setRoomId(roomId);
  packet_v1_room->setClientSessionId(clientSessionId);
  packet_v1_room->setRoomName(_roomMap->find(roomId)->second->getName());
  packet_v1_room->setClientLogin(clientLogin);

  _serverManager->Send(packet_v1_room, session);
}

void	Component_RoomManager::Recv_Leave(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);
  
  field_t roomId	  = packet_v1_room->getRoomId();
  field_t sessionId	  = session->getSessionId();
  char const *clientLogin = session->getLogin().c_str();

  if (_roomMap->find(roomId) != _roomMap->end())
    {
      Room *room = _roomMap->find(roomId)->second;
      if (room->removeConnected(sessionId))
	{
	  Send_Leave_OK(session, roomId);

	  std::map<field_t, Session*> *connected = room->getConnected();
	  std::map<field_t, Session *>::iterator it, end = connected->end();

	  for (it = connected->begin(); it != end ; ++it)
	    Send_Leaved(it->second, sessionId, roomId);
	  if (connected->size() == 0)
	    _roomMap->erase(roomId);
	}
      else
	Send_Leave_NOK_NOTINROOM(session, roomId);
    }
  else
    Send_Leave_NOK_NOTINROOM(session, roomId);
}

void	Component_RoomManager::Send_Leave_OK(Session *session, field_t roomId)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_LEAVE_OK);

  packet_v1_room->setRoomId(roomId);

  _serverManager->Send(_componentId, ROOM_LEAVE_OK, session);
}

void	Component_RoomManager::Send_Leave_NOK_NOTINROOM(Session *session, field_t roomId)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_LEAVE_NOK_NOTINROOM);

  packet_v1_room->setRoomId(roomId);
  _serverManager->Send(packet_v1_room, session);
}

void	Component_RoomManager::Send_Leaved(Session *session, field_t clientSessionId, field_t roomId)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_LEAVED);

  packet_v1_room->setRoomId(roomId);
  packet_v1_room->setClientSessionId(clientSessionId);

  _serverManager->Send(packet_v1_room, session);
}

void	Component_RoomManager::Recv_Message(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  field_t roomId	= packet_v1_room->getRoomId();
  field_t sessionId	= packet_v1_room->getSessionId();
  char const *message	= packet_v1_room->getMessage();

  if (_roomMap->find(roomId) != _roomMap->end())
    {
      Room *room = _roomMap->find(roomId)->second;

      std::map<field_t, Session*> *connected = room->getConnected();
      std::map<field_t, Session *>::iterator it, end = connected->end();

      for (it = connected->begin(); it != end ; ++it)
	{
	  if (it->first != sessionId)
	    Send_Message_RECV(it->second, message, roomId, sessionId);
	}
      Send_Message_ACK(session);
    }
}

void	Component_RoomManager::Send_Message_RECV(Session *session, char const *message, field_t roomId, field_t clientSessionId)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_MESSAGE_RECV);
  
  packet_v1_room->setRoomId(roomId);
  packet_v1_room->setMessage(message);
  packet_v1_room->setClientSessionId(clientSessionId);
  
  _serverManager->Send(packet_v1_room, session);
}

void	Component_RoomManager::Send_Message_ACK(Session *session)
{
  _serverManager->Send(_componentId, ROOM_MESSAGE_ACK, session);
}

void	Component_RoomManager::Recv_Kick(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  field_t roomId	  = packet_v1_room->getRoomId();
  field_t sessionId	  = session->getSessionId();
  field_t clientSessionId = packet_v1_room->getClientSessionId();

  if (_roomMap->find(roomId) != _roomMap->end())
    {
      Room *room = _roomMap->find(roomId)->second;
      if (room->removeConnected(clientSessionId))
	{
	  Send_Kick_OK(session, clientSessionId);
	  Send_User_Kicked(_sessionMap.find(clientSessionId)->second, packet_v1_room->getSessionId());

	  std::map<field_t, Session*> *connected = room->getConnected();
	  std::map<field_t, Session *>::iterator it, end = connected->end();

	  for (it = connected->begin(); it != end ; ++it)
	    Send_Kicked(it->second, clientSessionId);
	  if (connected->size() == 0)
	    _roomMap->erase(roomId);
	}
      else
	Send_Kick_NOK_NOTINROOM(session, clientSessionId);
    }
  else
    Send_Kick_NOK_NOTINROOM(session, clientSessionId);

}

void	Component_RoomManager::Send_Kicked(Session *session, field_t clientSessionId)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_KICKED);

  packet_v1_room->setClientSessionId(clientSessionId);

  _serverManager->Send(packet_v1_room, session);
}

void	Component_RoomManager::Send_Kick_OK(Session *session,field_t clientSessionId)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_KICK_OK);

  packet_v1_room->setClientSessionId(clientSessionId);

  _serverManager->Send(packet_v1_room, session);
}

void	Component_RoomManager::Send_Kick_NOK_NOTINROOM(Session *session, field_t clientSessionId)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_KICK_NOK_NOTINROOM);

  packet_v1_room->setClientSessionId(clientSessionId);

  _serverManager->Send(packet_v1_room, session);
}

void	Component_RoomManager::Send_User_Kicked(Session *session, field_t clientSessionId)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_USER_KICKED);

  packet_v1_room->setClientSessionId(clientSessionId);

  _serverManager->Send(packet_v1_room, session);
}

void	Component_RoomManager::Recv_Invite(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  char const *clientLogin  = session->getLogin().c_str();
  field_t clientSessionId  = packet_v1_room->getClientSessionId();

  Send_Invited(_sessionMap.find(clientSessionId)->second, clientLogin);
  Send_Invite_ACK(session);
}

void	Component_RoomManager::Send_Invite_ACK(Session *session)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_INVITE_ACK);

  _serverManager->Send(packet_v1_room, session);
}

void	Component_RoomManager::Recv_Start_Jam(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  field_t roomId = packet_v1_room->getRoomId();
  Room *room	 = _roomMap->find(roomId)->second;

  std::map<field_t, Session*> *connected = room->getConnected();
  std::map<field_t, Session *>::iterator it, end = connected->end();
  
  Send_Start_Jam_ACK(session);

  for (it = connected->begin(); it != end ; ++it)
    Send_Started_Jam(it->second, roomId);

  _serverManager->getComponentJam()->StartJam(roomId, room);
}

void	Component_RoomManager::Send_Start_Jam_ACK(Session *session)
{
  _serverManager->Send(_componentId, ROOM_START_JAM_ACK, session);
}

void	Component_RoomManager::Send_Started_Jam(Session *session, field_t roomId)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_STARTED_JAM);

  _serverManager->Send(packet_v1_room, session);
}

void	Component_RoomManager::Recv_Stop_Jam(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  field_t roomId = packet_v1_room->getRoomId();
  Room *room	 = _roomMap->find(roomId)->second;

  std::map<field_t, Session*> *connected = room->getConnected();
  std::map<field_t, Session *>::iterator it, end = connected->end();
  
  Send_Stop_Jam_ACK(session);

  for (it = connected->begin(); it != end ; ++it)
    Send_Stoped_Jam(it->second);

  _serverManager->getComponentJam()->StopJam(roomId);
}

void	Component_RoomManager::Send_Stop_Jam_ACK(Session *session)
{
  _serverManager->Send(_componentId, ROOM_STOP_JAM_ACK, session);
}

void	Component_RoomManager::Send_Stoped_Jam(Session *session)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_STOPED_JAM);

  _serverManager->Send(packet_v1_room, session);
}

void	Component_RoomManager::Send_Invited(Session *session, const char *clientLogin)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_INVITED);

  packet_v1_room->setClientLogin(clientLogin);

  _serverManager->Send(packet_v1_room, session);
}

void	Component_RoomManager::Connect(Session *)
{}

void	Component_RoomManager::Disconnect(Session *session)
{
 m_room::iterator it, end = _roomMap->end();

  for (it = _roomMap->begin(); it != end; ++it)
    {
      std::map<field_t, Session*> *connected = it->second->getConnected();

      if (connected->find(session->getSessionId()) != connected->end())
	{
	  it->second->removeConnected(session->getSessionId());
	  if (connected->size() == 0)
	      _roomMap->erase(it->first);
	  else
	    {
	      std::map<field_t, Session*>::iterator i, e = connected->end();
	      
	      for (i = connected->begin(); i != e; ++i)
		Send_Leaved(i->second, session->getSessionId(), it->first);
	    }
	}
    }
}

field_t	 Component_RoomManager::GenRoomId()
{
  field_t	roomId;

  do {
    roomId = _rng() % ((int)pow(2, PROTOV1_ROOM_ROOMID_SIZE));
  } while (! IsUniqId(roomId));
 return roomId;
}

bool	 Component_RoomManager::IsUniqId(field_t roomId) const
{
  return (_roomMap->find(roomId) == _roomMap->end());
}
