#include <Component_Friend.h>
#include <Bind_recv.h>

Component_Friend::Component_Friend(ClientManager *clientManager)
:  :IComponent(FRIEND_COMPONENTID), _clientManager(clientManager)
{
  _friendList = new v_friend();
}

Component_Friend::~Component_Friend()
{}

void	Component_Friend::BindingsRecv()
{
  (*_bindingsRecv)[FRIEND_JOINED] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Friend_Joined));
  (*_bindingsRecv)[FRIEND_LEAVED] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Friend_Leaved));
  (*_bindingsRecv)[FRIEND_ADD_OK] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Friend_Add_OK));
  (*_bindingsRecv)[FRIEND_ADD_NOK] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Friend_Add_NOK));
  (*_bindingsRecv)[FRIEND_DEL_OK] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Friend_Del_OK));
  (*_bindingsRecv)[FRIEND_DEL_NOK] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Friend_Del_NOK));
  (*_bindingsRecv)[FRIEND_LIST] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_Session::Recv_Friend_List));
}

void	Component_Friend::RegisteredRequests()
{
  // SEND requests
  (*_registeredRequests)[FRIEND_ADD] = 
    new Request(FRIEND_ADD, SEND, "Add friend request", RETRY);

  (*_registeredRequests)[FRIEND_DEL] = 
    new Request(FRIEND_DEL, SEND, "Del friend request", RETRY);

  // RECV requests
  (*_registeredRequests)[FRIEND_LEAVED] = 
    new Request(FRIEND_LEAVED, RECV, "Friend leaved", RESPONSETONOTHING);

  (*_registeredRequests)[FRIEND_JOINED] = 
    new Request(FRIEND_JOINED, RECV, "Friend Joined", RESPONSETONOTHING);

  (*_registeredRequests)[FRIEND_ADD_OK] = 
    new Request(FRIEND_ADD_OK, RECV, "Friend add request OK", SESSION_ADD_FRIEND);

  (*_registeredRequests)[FRIEND_ADD_NOK] = 
    new Request(FRIEND_ADD_NOK, RECV, "Friend add request NOK", SESSION_ADD_FRIEND);

  (*_registeredRequests)[FRIEND_DEL_OK] = 
    new Request(SESSION_DEL_FRIEND_OK, RECV, "Friend del request OK", SESSION_DEL_FRIEND);
  
  (*_registeredRequests)[FRIEND_DEL_NOK] = 
    new Request(SESSION_DEL_FRIEND_NOK, RECV, "Friend del request NOK", SESSION_DEL_FRIEND);
}

void		Component_Friend::Recv_Friend_Joined(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Friend const *packet_v1_friend =
    static_cast<Packet_v1_Friend const *>(packet_v1);

  char const *friendLogin = packet_v1_friend->getFriendLogin();

  std::cout << "FRIEND [" << friendLogin << "] has JOINED the application" << std::endl;
}

void		Component_Friend::Recv_Friend_Leaved(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Friend const *packet_v1_friend =
    static_cast<Packet_v1_Friend const *>(packet_v1);

  char const *friendLogin = packet_v1_friend->getFriendLogin();

  std::cout << "FRIEND [" << friendLogin << "] has LEAVED the application" << std::endl;
}

void		Component_Friend::Send_Friend_Add(char const *friendLogin)
{
  Packet_v1_Friend	*packet_v1_friend = new Packet_v1_Friend(SESSION_ADD_FRIEND);

  packet_v1_friend->setFriendLogin(friendLogin);

  std::cout << "SEND ADD FRIEND [" << friendLogin << "] " << std::endl;
  _clientManager->Send(packet_v1_friend, _session);
}
void		Component_Friend::Send_Friend_Del(char const *friendLogin)
{
  Packet_v1_Friend	*packet_v1_session = new Packet_v1_Friend(SESSION_DEL_FRIEND);

  packet_v1_friend->setFriendLogin(friendLogin);

  std::cout << "SEND DEL FRIEND [" << friendLogin << "] " << std::endl;
  _clientManager->Send(packet_v1_friend, _session);
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

void		Component_Friend::Recv_Friend_List(Packet_v1 const * packet_v1, Session *session)
{
 Packet_v1_Friend const *packet_v1_friend =
    static_cast<Packet_v1_Friend const *>(packet_v1);

 _friendList = packet_v1_friend->getFriendList();
}

bool		Component_Friend::IsFriend(std::string const &clientLogin) const
{
  for (unsigned int i = 0; i < _friendList->size(); ++i)
    {
      if (_friendList->at(i) == clientLogin)
	return true;
    }
  return false;
}
