#include <Component_Friend.h>
#include <Bind_recv.h>

Component_Friend::Component_Friend(ClientManager *clientManager)
  :IComponent(FRIEND_COMPONENTID), _clientManager(clientManager)
{}

Component_Friend::~Component_Friend()
{}

void	Component_Friend::BindingsRecv()
{
  (*_bindingsRecv)[FRIEND_JOINED] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Friend::Recv_Friend_Joined));

  (*_bindingsRecv)[FRIEND_LEAVED] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Friend::Recv_Friend_Leaved));

  (*_bindingsRecv)[FRIEND_ADD_OK] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Friend::Recv_Friend_Add_OK));

  (*_bindingsRecv)[FRIEND_ADD_NOK] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Friend::Recv_Friend_Add_NOK));

  (*_bindingsRecv)[FRIEND_DEL_OK] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Friend::Recv_Friend_Del_OK));

  (*_bindingsRecv)[FRIEND_DEL_NOK] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Friend::Recv_Friend_Del_NOK));
}

void	Component_Friend::RegisteredRequests()
{
  // SEND requests
  (*_registeredRequests)[FRIEND_ADD] = 
    new Request(FRIEND_ADD, SEND, "ADD", RETRY);

  (*_registeredRequests)[FRIEND_DEL] = 
    new Request(FRIEND_DEL, SEND, "DEL", RETRY);

  (*_registeredRequests)[FRIEND_JOINED_ACK] = 
    new Request(FRIEND_JOINED_ACK, SEND, "JOINED", NORETRY);

  (*_registeredRequests)[FRIEND_LEAVED_ACK] = 
    new Request(FRIEND_LEAVED_ACK, SEND, "LEAVED_ACK", NORETRY);

  // RECV requests
  (*_registeredRequests)[FRIEND_LEAVED] = 
    new Request(FRIEND_LEAVED, RECV, "LEAVED", RESPONSETONOTHING);

  (*_registeredRequests)[FRIEND_JOINED] = 
    new Request(FRIEND_JOINED, RECV, "JOINED", RESPONSETONOTHING);

  (*_registeredRequests)[FRIEND_ADD_OK] = 
    new Request(FRIEND_ADD_OK, RECV, "ADD_OK", FRIEND_ADD);

  (*_registeredRequests)[FRIEND_ADD_NOK] = 
    new Request(FRIEND_ADD_NOK, RECV, "ADD_NOK", FRIEND_ADD);

  (*_registeredRequests)[FRIEND_DEL_OK] = 
    new Request(FRIEND_DEL_OK, RECV, "DEL_OK", FRIEND_DEL);
  
  (*_registeredRequests)[FRIEND_DEL_NOK] = 
    new Request(FRIEND_DEL_NOK, RECV, "DEL_NOK", FRIEND_DEL);
}

void		Component_Friend::Recv_Friend_Joined(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Friend const *packet_v1_friend =
    static_cast<Packet_v1_Friend const *>(packet_v1);

  char const *friendLogin = packet_v1_friend->getFriendLogin();

  std::cout << "FRIEND [" << friendLogin << "] has JOINED the application" << std::endl;
  Send_Friend_Joined_ACK(session);
}

void		Component_Friend::Recv_Friend_Leaved(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Friend const *packet_v1_friend =
    static_cast<Packet_v1_Friend const *>(packet_v1);

  char const *friendLogin = packet_v1_friend->getFriendLogin();

  std::cout << "FRIEND [" << friendLogin << "] has LEAVED the application" << std::endl;
  Send_Friend_Leaved_ACK(session);
}

void		Component_Friend::Send_Friend_Add(Session *session, char const *friendLogin)
{
  Packet_v1_Friend	*packet_v1_friend = new Packet_v1_Friend(FRIEND_ADD);

  packet_v1_friend->setFriendLogin(friendLogin);

  std::cout << "SEND ADD FRIEND [" << friendLogin << "] " << std::endl;
  _clientManager->Send(packet_v1_friend, session);
}
void		Component_Friend::Send_Friend_Del(Session* session, char const *friendLogin)
{
  Packet_v1_Friend	*packet_v1_friend = new Packet_v1_Friend(FRIEND_DEL);

  packet_v1_friend->setFriendLogin(friendLogin);

  std::cout << "SEND DEL FRIEND [" << friendLogin << "] " << std::endl;
  _clientManager->Send(packet_v1_friend, session);
}

void		Component_Friend::Recv_Friend_Add_OK(Packet_v1 const *packet_v1, Session *session)
{
 Packet_v1_Friend const *packet_v1_friend =
    static_cast<Packet_v1_Friend const *>(packet_v1);

  char const *friendLogin = packet_v1_friend->getFriendLogin();

  std::cout << "FRIEND [" << friendLogin << "] has been ADDED" << std::endl;
}

void		Component_Friend::Recv_Friend_Add_NOK(Packet_v1 const *packet_v1, Session *session)
{
 Packet_v1_Friend const *packet_v1_friend =
    static_cast<Packet_v1_Friend const *>(packet_v1);

  char const *friendLogin = packet_v1_friend->getFriendLogin();

  std::cout << "FRIEND [" << friendLogin << "] has NOT been ADDED" << std::endl;
}

void		Component_Friend::Recv_Friend_Del_OK(Packet_v1 const *packet_v1, Session *session)
{
 Packet_v1_Friend const *packet_v1_friend =
    static_cast<Packet_v1_Friend const *>(packet_v1);

  char const *friendLogin = packet_v1_friend->getFriendLogin();

  std::cout << "FRIEND [" << friendLogin << "] has been DELETED" << std::endl;
}

void		Component_Friend::Recv_Friend_Del_NOK(Packet_v1 const *packet_v1, Session *session)
{
 Packet_v1_Friend const *packet_v1_friend =
    static_cast<Packet_v1_Friend const *>(packet_v1);

  char const *friendLogin = packet_v1_friend->getFriendLogin();

  std::cout << "FRIEND [" << friendLogin << "] has NOT been DELETED" << std::endl;
}

void		Component_Friend::Send_Friend_Joined_ACK(Session *session)
{
  std::cout << ">>>>>>>>>>>> SEND [FRIEND_JOINED_ACK] <<<<<<<<<<<<" << std::endl;
  _clientManager->Send(_componentId, FRIEND_JOINED_ACK, session);
}

void		Component_Friend::Send_Friend_Leaved_ACK(Session *session)
{
  std::cout << ">>>>>>>>>>>> SEND [FRIEND LEAVED_ACK] <<<<<<<<<<<<" << std::endl;
  _clientManager->Send(_componentId, FRIEND_LEAVED_ACK, session);
}

void		Component_Friend::Connect(Session *)
{}

void		Component_Friend::Disconnect(Session *)
{}

bool		Component_Friend::IsFriend(Session *session, std::string const &clientLogin) const
{
  std::list<std::string> friendList = session->getFriendList();
  std::list<std::string>::iterator it, end = friendList.end();

  for (it = friendList.begin(); it != end; ++it)
    {
      if ((*it) == clientLogin)
	return true;
    }
  return false;
}
