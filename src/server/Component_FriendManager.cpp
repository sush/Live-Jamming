#include <Component_FriendManager.h>
#include <Bind_recv.h>

Component_FriendManager::Component_FriendManager(ServerManager * serverManager)
  :IComponent(FRIEND_COMPONENTID), _serverManager(serverManager)
{}

Component_FriendManager::~Component_FriendManager()
{}

void		Component_FriendManager::Send_Friend_Joined(Session *session, const char *clientLogin)
{
  Packet_v1_Friend *packet_v1_friend = new Packet_v1_Friend(FRIEND_JOINED);

  packet_v1_friend->setFriendLogin(clientLogin);
  _serverManager->Send(packet_v1_friend, session);
}

void		Component_FriendManager::Send_Friend_Leaved(Session *session, const char *clientLogin)
{
  Packet_v1_Friend *packet_v1_friend = new Packet_v1_Friend(FRIEND_LEAVED);

  packet_v1_friend->setFriendLogin(clientLogin);
  _serverManager->Send(packet_v1_friend, session);
}

void		Component_FriendManager::Recv_Friend_Add(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Friend	const *packet_v1_friend =
    static_cast<Packet_v1_Friend const *>(packet_v1);

  char const * friendLogin = packet_v1_friend->getFriendLogin();
  // call userModule->AddFriend(session->getLogin(), friendLogin);
  // if ok 
  // Send_Add_Friend_OK(session, friendLogin);
  // else
  // Send_Add_Friend_NOK(session, friendLogin);
}

void		Component_FriendManager::Recv_Friend_Del(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Friend	const *packet_v1_friend =
    static_cast<Packet_v1_Friend const *>(packet_v1);

  char const * friendLogin = packet_v1_friend->getFriendLogin();
  // call userModule->DelFriend(session->getLogin(), friendLogin);
  // if ok 
  // Send_Del_Friend_OK(session, friendLogin);
  // else
  // Send_Del_Friend_NOK(session, friendLogin);
}

void		Component_FriendManager::Send_Friend_Add_OK(Session *session, char const *friendLogin)
{
  Packet_v1_Friend *packet_v1_friend = new Packet_v1_Friend(FRIEND_ADD_OK);

  packet_v1_friend->setFriendLogin(friendLogin);
  _serverManager->Send(packet_v1_friend, session);
}

void		Component_FriendManager::Send_Friend_Add_NOK(Session *session, char const *friendLogin)
{
  Packet_v1_Friend *packet_v1_friend = new Packet_v1_Friend(FRIEND_ADD_NOK);

  packet_v1_friend->setFriendLogin(friendLogin);
  _serverManager->Send(packet_v1_friend, session);
}

void		Component_FriendManager::Send_Friend_Del_OK(Session *session, char const *friendLogin)
{
  Packet_v1_Friend *packet_v1_friend = new Packet_v1_Friend(FRIEND_DEL_OK);

  packet_v1_friend->setFriendLogin(friendLogin);
  _serverManager->Send(packet_v1_friend, session);
}

void		Component_FriendManager::Send_Friend_Del_NOK(Session *session, char const *friendLogin)
{
  Packet_v1_Friend *packet_v1_friend = new Packet_v1_Friend(FRIEND_DEL_NOK);

  packet_v1_friend->setFriendLogin(friendLogin);
  _serverManager->Send(packet_v1_friend, session);
}

void		Component_FriendManager::Send_Friend_List(Session *session, std::vector<std::string> const & friendList)
{

  Packet_v1_Friend *packet_v1_friend = new Packet_v1_Friend(FRIEND_LIST);

  packet_v1_friend->setFriendList(friendList);
  _serverManager->Send(packet_v1_friend, session);
}

void		Component_FriendManager::Disconnect(Session * session)
{
  // m_Session::iterator it, end		= _sessionMap->end();
  // std::vector<std::string> friendList	= session->getFriendList();

  // for (it = _sessionMap->begin(); it != end; ++it)
  //   {
  //     for (unsigned int i = 0; i < friendList.size(); ++i)
  // 	{
  // 	  if (it->second->getLogin() == friendList[i])
  // 	    Send_Friend_Leaved(it->second, session->getLogin().c_str());
  // 	}
  //   }
}

void		Component_FriendManager::BindingsRecv()
{
  (*_bindingsRecv)[FRIEND_ADD] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_FriendManager::Recv_Friend_Add));

  (*_bindingsRecv)[FRIEND_DEL] =
    new Bind_recv(this, static_cast<IComponent::pMethod>(&Component_FriendManager::Recv_Friend_Del));
}

void	Component_FriendManager::RegisteredRequests()
{
  // SEND requests 
  (*_registeredRequests)[FRIEND_JOINED] = 
    new Request(FRIEND_JOINED, SEND, "Session friend joined notification", RETRY);

  (*_registeredRequests)[FRIEND_LEAVED] = 
    new Request(FRIEND_LEAVED, SEND, "Session friend leaved notification", RETRY);

  (*_registeredRequests)[FRIEND_ADD_OK] = 
    new Request(FRIEND_ADD_OK, SEND, "Session friend add OK notification", NORETRY);

  (*_registeredRequests)[FRIEND_ADD_NOK] = 
    new Request(FRIEND_ADD_NOK, SEND, "Session friend add NOK notification", NORETRY);

  (*_registeredRequests)[FRIEND_DEL_OK] = 
    new Request(FRIEND_DEL_OK, SEND, "Session friend del OK notification", NORETRY);

  (*_registeredRequests)[FRIEND_DEL_NOK] = 
    new Request(FRIEND_DEL_NOK, SEND, "Session friend del NOK notification", NORETRY);

  // RECV requests
  (*_registeredRequests)[FRIEND_ADD] = 
    new Request(FRIEND_ADD, RECV, "Add friend request", RESPONSETONOTHING);

  (*_registeredRequests)[FRIEND_DEL] = 
    new Request(FRIEND_DEL, RECV, "Del friend request", RESPONSETONOTHING);

  (*_registeredRequests)[FRIEND_JOINED_ACK] = 
    new Request(FRIEND_JOINED_ACK, RECV, "Del friend request", FRIEND_JOINED);

  (*_registeredRequests)[FRIEND_LEAVED_ACK] = 
    new Request(FRIEND_LEAVED_ACK, RECV, "Del friend request", FRIEND_LEAVED);

}
