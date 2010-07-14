#include <Component_FriendManager.h>
#include <Bind_recv.h>

Component_FriendManager::Component_FriendManager(ServerManager * serverManager)
  :IComponent(FRIEND_COMPONENTID), _serverManager(serverManager), _sessionMap(serverManager->getSessionMap())
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
  bool existing		   = false;

  std::list<std::string>::iterator it, end = session->getFriendList().end();
  for (it = session->getFriendList().begin(); it != end; ++it)
    {
      if ((*it) == friendLogin)
	{
	  existing = true;
	  Send_Friend_Add_NOK(session, friendLogin);
	  break;
	}
    }

  if (!existing)
    {
      // call userModule->AddFriend(session->getLogin(), friendLogin);
      session->getFriendList().push_back(friendLogin);
      Send_Friend_Add_OK(session, friendLogin);
    }
}

void		Component_FriendManager::Recv_Friend_Del(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Friend	const *packet_v1_friend =
    static_cast<Packet_v1_Friend const *>(packet_v1);

  char const * friendLogin = packet_v1_friend->getFriendLogin();
  bool existing		   = false;

  std::list<std::string>::iterator it, end = session->getFriendList().end();
  for (it = session->getFriendList().begin(); it != end; ++it)
    {
      if ((*it) == friendLogin)
	{
	  existing = true;
	  // call userModule->DelFriend(session->getLogin(), friendLogin);
	  session->getFriendList().erase(it);
	  Send_Friend_Del_OK(session, friendLogin);
	  break;
	}
    }

  if (!existing)
    Send_Friend_Del_NOK(session, friendLogin);
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

void		Component_FriendManager::Connect(Session *session)
{
  // session->setFriendList(userModule->getFriendList);
}

void		Component_FriendManager::Disconnect(Session * session)
{
  ServerManager::m_Session::iterator it, end	= _sessionMap.end();
  std::list<std::string> friendList		= session->getFriendList();

  for (it = _sessionMap.begin(); it != end; ++it)
    {
      std::list<std::string>::iterator it2, end2 = friendList.end();
      for (it2 = friendList.begin(); it2 != end2; ++it2)
  	{
  	  if (it->second->getLogin() == (*it2))
  	    Send_Friend_Leaved(it->second, session->getLogin().c_str());
  	}
    }
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
