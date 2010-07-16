#include <Component_Room.h>
#include <Bind_recv.h>

Component_Room::Component_Room(ClientManager *clientManager)
  : IComponent(ROOM_COMPONENTID), _clientManager(clientManager)
{
}

Component_Room::~Component_Room() {}

void		Component_Room::BindingsRecv()
{
    (*_bindingsRecv)[ROOM_JOIN_OK] =
      new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Room::Recv_Join_OK),
                    static_cast<Proxy*>(_clientManager), static_cast<Proxy::pMethod>(&Proxy::roomResponse));

    (*_bindingsRecv)[ROOM_JOIN_NOK_ALREADYINROOM] =
      new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Room::Recv_Join_NOK_ALREADYINROOM));

    (*_bindingsRecv)[ROOM_JOINED] =
      new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Room::Recv_Joined),
                    static_cast<Proxy*>(_clientManager), static_cast<Proxy::pMethod>(&Proxy::roomResponse));

  (*_bindingsRecv)[ROOM_MESSAGE_ACK] =
    new Bind_recv(0, 0);

  (*_bindingsRecv)[ROOM_MESSAGE_RECV] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Room::Recv_Message_RECV),
                  static_cast<Proxy*>(_clientManager), static_cast<Proxy::pMethod>(&Proxy::roomResponse));
  
  (*_bindingsRecv)[ROOM_LEAVE_OK] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Room::Recv_Leave_OK),
                    static_cast<Proxy*>(_clientManager), static_cast<Proxy::pMethod>(&Proxy::roomResponse));
  
  (*_bindingsRecv)[ROOM_LEAVE_NOK_NOTINROOM] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Room::Recv_Leave_NOK_NOTINROOM));
  
  (*_bindingsRecv)[ROOM_LEAVED] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Room::Recv_Leaved),
                    static_cast<Proxy*>(_clientManager), static_cast<Proxy::pMethod>(&Proxy::roomResponse));

  (*_bindingsRecv)[ROOM_KICK_OK] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Room::Recv_Kick_OK));

  (*_bindingsRecv)[ROOM_KICK_NOK_NOTINROOM] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Room::Recv_Kick_NOK_NOTINROOM));

  (*_bindingsRecv)[ROOM_INVITED] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Room::Recv_Invited));

  (*_bindingsRecv)[ROOM_USER_KICKED] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Room::Recv_User_Kicked));

  (*_bindingsRecv)[ROOM_STARTED_JAM] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Room::Recv_Started_Jam));

  (*_bindingsRecv)[ROOM_STOPED_JAM] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Room::Recv_Stoped_Jam));

  (*_bindingsRecv)[ROOM_START_JAM_ACK] =
    new Bind_recv(0, 0);

  (*_bindingsRecv)[ROOM_START_JAM_ACK] =
    new Bind_recv(0, 0);

  (*_bindingsRecv)[ROOM_KICKED] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Room::Recv_Kicked));
}

void	Component_Room::RegisteredRequests()
{
  // SEND requests
  (*_registeredRequests)[ROOM_JOIN] = 
    new Request(ROOM_JOIN, SEND, "JOIN", RETRY);

  (*_registeredRequests)[ROOM_JOINED_ACK] = 
    new Request(ROOM_JOINED_ACK, SEND, "JOINED_ACK", NORETRY);

  (*_registeredRequests)[ROOM_MESSAGE] = 
    new Request(ROOM_MESSAGE, SEND, "MESSAGE", RETRY);

  (*_registeredRequests)[ROOM_MESSAGE_RECV_ACK] = 
    new Request(ROOM_MESSAGE_RECV_ACK, SEND, "MESSAGE_RECV_ACK", NORETRY);

  (*_registeredRequests)[ROOM_LEAVE] = 
    new Request(ROOM_LEAVE, SEND, "LEAVE", RETRY);

  (*_registeredRequests)[ROOM_LEAVED_ACK] = 
    new Request(ROOM_LEAVED_ACK, SEND, "LEAVED_ACK", NORETRY);

  (*_registeredRequests)[ROOM_INVITE] = 
    new Request(ROOM_LEAVED_ACK, SEND, "INVITE", RETRY);

  (*_registeredRequests)[ROOM_KICK] = 
    new Request(ROOM_KICK, SEND, "KICK", RETRY);

  (*_registeredRequests)[ROOM_START_JAM] = 
    new Request(ROOM_START_JAM, SEND, "START_JAM", RETRY);

  (*_registeredRequests)[ROOM_STOP_JAM] = 
    new Request(ROOM_STOP_JAM, SEND, "STOP_JAM", RETRY);

  (*_registeredRequests)[ROOM_KICKED_ACK] = 
    new Request(ROOM_KICKED_ACK, SEND, "KICKED_ACK", NORETRY);

  (*_registeredRequests)[ROOM_INVITED_ACK] = 
    new Request(ROOM_INVITED_ACK, SEND, "INVITED_ACK", NORETRY);

  (*_registeredRequests)[ROOM_STARTED_JAM_ACK] = 
    new Request(ROOM_STARTED_JAM_ACK, SEND, "STARTED_JAM_ACK", NORETRY);

  (*_registeredRequests)[ROOM_STOPED_JAM_ACK] = 
    new Request(ROOM_STOPED_JAM_ACK, SEND, "STOPED_JAM_ACK", NORETRY);

  (*_registeredRequests)[ROOM_USER_KICKED_ACK] = 
    new Request(ROOM_USER_KICKED_ACK, SEND, "USER_KICKED_ACK", NORETRY);

  // RECV requests
  (*_registeredRequests)[ROOM_JOIN_OK] = 
    new Request(ROOM_JOIN_OK, RECV, "JOIN_OK", ROOM_JOIN);

  (*_registeredRequests)[ROOM_JOIN_NOK_ALREADYINROOM] = 
    new Request(ROOM_JOIN_NOK_ALREADYINROOM, RECV, "JOIN_NOK_ALREADYINROOM", ROOM_JOIN);

  (*_registeredRequests)[ROOM_JOINED] = 
    new Request(ROOM_JOINED, RECV, "JOINED", RESPONSETONOTHING);

  (*_registeredRequests)[ROOM_MESSAGE_ACK] = 
    new Request(ROOM_MESSAGE_ACK, RECV, "MESSAGE_ACK", ROOM_MESSAGE);

  (*_registeredRequests)[ROOM_MESSAGE_RECV] = 
    new Request(ROOM_MESSAGE_RECV, RECV, "MESSAGE_RECV", RESPONSETONOTHING);

  (*_registeredRequests)[ROOM_LEAVE_OK] = 
    new Request(ROOM_LEAVE_OK, RECV, "LEAVE_OK", ROOM_LEAVE);

  (*_registeredRequests)[ROOM_LEAVE_NOK_NOTINROOM] = 
    new Request(ROOM_LEAVE_NOK_NOTINROOM, RECV, "LEAVE_NOK_NOTINROOM", ROOM_LEAVE);

  (*_registeredRequests)[ROOM_LEAVED] = 
    new Request(ROOM_LEAVED, RECV, "LEAVED", RESPONSETONOTHING);

  (*_registeredRequests)[ROOM_INVITED] = 
    new Request(ROOM_INVITED, RECV, "INVITED", RESPONSETONOTHING);

  (*_registeredRequests)[ROOM_USER_KICKED] = 
    new Request(ROOM_USER_KICKED, RECV, "USER_KICKED", RESPONSETONOTHING);

  (*_registeredRequests)[ROOM_INVITE_ACK] = 
    new Request(ROOM_INVITE_ACK, RECV, "INVITE_ACK", ROOM_INVITE);

  (*_registeredRequests)[ROOM_KICK_OK] = 
    new Request(ROOM_KICK_OK, RECV, "KICK_OK", ROOM_KICK);

  (*_registeredRequests)[ROOM_KICK_NOK_NOTINROOM] = 
    new Request(ROOM_KICK_NOK_NOTINROOM, RECV, "KICK_NOK_NOTINROOM", ROOM_KICK);

  (*_registeredRequests)[ROOM_START_JAM_ACK] = 
    new Request(ROOM_START_JAM_ACK, RECV, "START_JAM_ACK", ROOM_START_JAM);

  (*_registeredRequests)[ROOM_STOP_JAM_ACK] = 
    new Request(ROOM_STOP_JAM_ACK, RECV, "STOP_JAM_ACK", ROOM_STOP_JAM);

  (*_registeredRequests)[ROOM_STARTED_JAM] = 
    new Request(ROOM_STARTED_JAM, RECV, "STARTED_JAM", RESPONSETONOTHING);

  (*_registeredRequests)[ROOM_STOPED_JAM] = 
    new Request(ROOM_STOPED_JAM, RECV, "STOPED_JAM", RESPONSETONOTHING);

  (*_registeredRequests)[ROOM_KICKED] = 
    new Request(ROOM_KICKED, RECV, "KICKED", RESPONSETONOTHING);
}

void		Component_Room::Send_Join(Session *session, char * const name)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_JOIN);
  packet_v1_room->setRoomName(name);

  _clientManager->Send(packet_v1_room, session);
}

void		Component_Room::Recv_Join_OK(Packet_v1 const *packet_v1, Session *)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  field_t roomId = packet_v1_room->getRoomId();
  char const *roomName = packet_v1_room->getRoomName();

  if (_roomMap.find(roomId) == _roomMap.end())
    _roomMap[roomId] = new Room(roomName);
}

void		Component_Room::Recv_Join_NOK_ALREADYINROOM(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  field_t roomId = packet_v1_room->getRoomId();
  // in case of lost packet check if user not in chan if so add him to it
  if (_roomMap.find(roomId) != _roomMap.end())
    {
      Room *chan = _roomMap.find(roomId)->second;
      chan->addConnected(session, session->getSessionId());
    }
}

void		Component_Room::Recv_Joined(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  field_t	clientSessionId = packet_v1_room->getClientSessionId();
  char const *	clientLogin= packet_v1_room->getClientLogin();
  field_t	roomId = packet_v1_room->getRoomId();
  Room	*chan = _roomMap.find(roomId)->second;

  chan->addConnected(0, clientSessionId);
  Send_Joined_ACK(session);
}

void		Component_Room::Send_Joined_ACK(Session *session)
{
  _clientManager->Send(_componentId, ROOM_JOINED_ACK, session);
}

void		Component_Room::Send_Message(Session *session, char const *message, field_t roomId)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_MESSAGE);

  packet_v1_room->setRoomId(roomId);
  packet_v1_room->setMessage(message);
  _clientManager->Send(packet_v1_room, session);
}

void		Component_Room::Recv_Message_RECV(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  //  field_t clientSessionId = packet_v1_room->getClientSessionId();
  field_t roomId = packet_v1_room->getRoomId();
  char const * message = packet_v1_room->getMessage();

  // implement gui receive message
  Send_Message_RECV_ACK(session);
}

void		Component_Room::Send_Message_RECV_ACK(Session *session)
{
  _clientManager->Send(_componentId, ROOM_MESSAGE_RECV_ACK, session);
}

void		Component_Room::Send_Leave(Session *session, field_t roomId)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_LEAVE);

  packet_v1_room->setRoomId(roomId);

  _clientManager->Send(packet_v1_room, session);
}

void		Component_Room::Recv_Leave_OK(Packet_v1 const *packet_v1, Session *)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  field_t roomId = packet_v1_room->getRoomId();

  _roomMap.erase(roomId);
}

void		Component_Room::Recv_Leave_NOK_NOTINROOM(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  field_t roomId = packet_v1_room->getRoomId();
  // in case of lost packet check if user still in chan, if so delete him
  if (_roomMap.find(roomId) != _roomMap.end())
    {
      Room *chan = _roomMap.find(roomId)->second;
      chan->removeConnected(session->getSessionId());
      _roomMap.erase(roomId);
    }
}

void		Component_Room::Recv_Leaved(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  field_t	roomId = packet_v1_room->getRoomId();
  field_t	clientSessionId = packet_v1_room->getClientSessionId();
  char const *	clientLogin = packet_v1_room->getClientLogin();

  Room *chan = _roomMap.find(roomId)->second;
  chan->removeConnected(clientSessionId);
  Send_Leaved_ACK(session);
}

void		Component_Room::Send_Leaved_ACK(Session *session)
{
  _clientManager->Send(_componentId, ROOM_LEAVED_ACK, session);
}

void		Component_Room::Send_Invite(Session *session, char const *clientLogin, field_t roomId)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_INVITE);

  packet_v1_room->setClientLogin(clientLogin);
  packet_v1_room->setRoomId(roomId);

  _clientManager->Send(packet_v1_room, session);
}

void		Component_Room::Send_Kick(Session *session, field_t clientSessionId, field_t roomId)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_KICK);

  packet_v1_room->setClientSessionId(clientSessionId);
  packet_v1_room->setRoomId(roomId);

  _clientManager->Send(packet_v1_room, session);
}

void		Component_Room::Send_Start_Jam(Session *session, field_t roomId)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_START_JAM);

  packet_v1_room->setRoomId(roomId);

  _clientManager->Send(packet_v1_room, session);
}

void		Component_Room::Send_Stop_Jam(Session *session, field_t roomId)
{
  Packet_v1_Room *packet_v1_room = new Packet_v1_Room(ROOM_STOP_JAM);

  packet_v1_room->setRoomId(roomId);

  _clientManager->Send(packet_v1_room, session);
}

void		Component_Room::Send_Kicked_ACK(Session *session)
{
  _clientManager->Send(_componentId, ROOM_KICKED_ACK, session);
}

void		Component_Room::Send_Invited_ACK(Session *session)
{
  _clientManager->Send(_componentId, ROOM_INVITED_ACK, session);
}

void		Component_Room::Send_Started_Jam_ACK(Session *session)
{
  _clientManager->Send(_componentId, ROOM_STARTED_JAM_ACK, session);
}

void		Component_Room::Send_Stoped_Jam_ACK(Session *session)
{
  _clientManager->Send(_componentId, ROOM_STOPED_JAM_ACK, session);
}

void		Component_Room::Send_User_Kicked_ACK(Session *session)
{
  _clientManager->Send(_componentId, ROOM_USER_KICKED_ACK, session);
}

void		Component_Room::Recv_Kick_OK(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  field_t clientSessionId = packet_v1_room->getClientSessionId();

  // clientSessionId has been kicked !
}

void		Component_Room::Recv_Kick_NOK_NOTINROOM(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  field_t clientSessionId = packet_v1_room->getClientSessionId();

  // clientSessionId has not been kicked not in the room anymore!
}

void		Component_Room::Recv_Invited(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  field_t clientSessionId = packet_v1_room->getClientSessionId();

  // clientSessionId has invited you to a room !

  Send_Invited_ACK(session);
}

void		Component_Room::Recv_User_Kicked(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  field_t clientSessionId = packet_v1_room->getClientSessionId();
  // clientSessionId has kicked you from the room !
  Send_User_Kicked_ACK(session);
}

void		Component_Room::Recv_Started_Jam(Packet_v1 const *packet_v1, Session *session)
{
  // JAM HAS STARTED
  Send_Started_Jam_ACK(session);
}

void		Component_Room::Recv_Stoped_Jam(Packet_v1 const *packet_v1, Session *session)
{
  // JAM HAS STOPPED
  Send_Stoped_Jam_ACK(session);
}

void		Component_Room::Recv_Kicked(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Room const *packet_v1_room = 
    static_cast<Packet_v1_Room const *>(packet_v1);

  field_t clientSessionId = packet_v1_room->getClientSessionId();

  // clientSessionId has been kicked of the room

  Send_Kicked_ACK(session);
}

void		Component_Room::Connect(Session *)
{}

void		Component_Room::Disconnect(Session *)
{}
