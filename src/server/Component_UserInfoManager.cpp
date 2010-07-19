#include <Component_UserInfoManager.h>
#include <Bind_recv.h>

Component_UserInfoManager::Component_UserInfoManager(ServerManager *serverManager)
  :IComponent(USERINFO_COMPONENTID), _serverManager(serverManager), _sessionMap(serverManager->getSessionMap())
{}

Component_UserInfoManager::~Component_UserInfoManager() {}

void    Component_UserInfoManager::BindingsRecv()
{
  (*_bindingsRecv)[USERINFO_GETINFO_REQUEST] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_UserInfoManager::Recv_GetInfo_Request));

  (*_bindingsRecv)[USERINFO_GETAVATAR_REQUEST] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_UserInfoManager::Recv_GetAvatar_Request));
}

void    Component_UserInfoManager::RegisteredRequests()
{
  // SEND requests                                                                                                                                                                                                                           
  (*_registeredRequests)[USERINFO_GETINFO_RESPONSE_OK] =
    new Request(USERINFO_GETINFO_RESPONSE_OK, SEND, "GETINFO_RESPONSE_OK", NORETRY);

  (*_registeredRequests)[USERINFO_GETINFO_RESPONSE_NOK_INVALIDUSER] =
    new Request(USERINFO_GETINFO_RESPONSE_NOK_INVALIDUSER, SEND, "GETINFO_RESPONSE_NOK_INVALIDUSER", NORETRY);

  (*_registeredRequests)[USERINFO_GETAVATAR_RESPONSE_OK] =
    new Request(USERINFO_GETAVATAR_RESPONSE_OK, SEND, "GETAVATAR_RESPONSE_OK", NORETRY);

  (*_registeredRequests)[USERINFO_GETAVATAR_RESPONSE_NOK_INVALIDUSER] =
    new Request(USERINFO_GETAVATAR_RESPONSE_NOK_INVALIDUSER, SEND, "GETAVATAR_RESPONSE_NOK_INVALIDUSER", NORETRY);


  // RECV requests                                                                                                                                                                                                                           
  (*_registeredRequests)[USERINFO_GETINFO_REQUEST] =
    new Request(USERINFO_GETINFO_REQUEST, RECV, "GETINFO_REQUEST", RESPONSETONOTHING);

  (*_registeredRequests)[USERINFO_GETAVATAR_REQUEST] =
    new Request(USERINFO_GETAVATAR_REQUEST, RECV, "GETAVATAR_REQUEST", RESPONSETONOTHING);
}

void    Component_UserInfoManager::Send_GetInfo_Response_OK(Session *session, field_t clientSessionId)
{
  Packet_v1_UserInfo *packet_v1_userinfo = new Packet_v1_UserInfo(USERINFO_GETINFO_RESPONSE_OK);

  assert(_sessionMap.find(clientSessionId) != _sessionMap.end());
  packet_v1_userinfo->setClientSessionId(clientSessionId);
  packet_v1_userinfo->setUserInfo(_sessionMap.find(clientSessionId)->second->getUserInfo());

  _serverManager->Send(packet_v1_userinfo, session);
}

void    Component_UserInfoManager::Send_GetInfo_Response_NOK_InvalidUser(Session *session, field_t clientSessionId)
{
  Packet_v1_UserInfo *packet_v1_userinfo = new Packet_v1_UserInfo(USERINFO_GETINFO_RESPONSE_NOK_INVALIDUSER);

  assert(_sessionMap.find(clientSessionId) == _sessionMap.end());
  packet_v1_userinfo->setClientSessionId(clientSessionId);

  _serverManager->Send(packet_v1_userinfo, session);
}

void    Component_UserInfoManager::Recv_GetInfo_Request(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_UserInfo const *packet_v1_userinfo =
    static_cast<Packet_v1_UserInfo const *>(packet_v1);

  field_t clientSessionId = packet_v1_userinfo->getClientSessionId();

  if (_sessionMap.find(clientSessionId) != _sessionMap.end())
    Send_GetInfo_Response_OK(session, clientSessionId);
  else
    Send_GetInfo_Response_NOK_InvalidUser(session, clientSessionId);
}


void    Component_UserInfoManager::Send_GetAvatar_Response_OK(Session *session, field_t clientSessionId)
{
  Packet_v1_UserInfo *packet_v1_userinfo = new Packet_v1_UserInfo(USERINFO_GETAVATAR_RESPONSE_OK);

  assert(_sessionMap.find(clientSessionId) != _sessionMap.end());
  packet_v1_userinfo->setClientSessionId(clientSessionId);
  packet_v1_userinfo->setAvatar(_sessionMap.find(clientSessionId)->second->getAvatar());

  _serverManager->Send(packet_v1_userinfo, session);
}

void    Component_UserInfoManager::Send_GetAvatar_Response_NOK_InvalidUser(Session *session, field_t clientSessionId)
{
  Packet_v1_UserInfo *packet_v1_userinfo = new Packet_v1_UserInfo(USERINFO_GETAVATAR_RESPONSE_NOK_INVALIDUSER);

  assert(_sessionMap.find(clientSessionId) == _sessionMap.end());
  packet_v1_userinfo->setClientSessionId(clientSessionId);

  _serverManager->Send(packet_v1_userinfo, session);
}

void    Component_UserInfoManager::Recv_GetAvatar_Request(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_UserInfo const *packet_v1_userinfo =
    static_cast<Packet_v1_UserInfo const *>(packet_v1);

  field_t clientSessionId = packet_v1_userinfo->getClientSessionId();

  if (_sessionMap.find(clientSessionId) != _sessionMap.end())
    Send_GetAvatar_Response_OK(session, clientSessionId);
  else
    Send_GetAvatar_Response_NOK_InvalidUser(session, clientSessionId);
}
