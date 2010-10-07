#include <Component_UserInfo.h>
#include <Bind_recv.h>

Component_UserInfo::Component_UserInfo(ClientManager *clientManager)
  :IComponent(USERINFO_COMPONENTID), _clientManager(clientManager),
   _userMap(clientManager->getUserMap()), _avatarMap(clientManager->getAvatarMap())
{}

Component_UserInfo::~Component_UserInfo() {}

void    Component_UserInfo::BindingsRecv()
{
  (*_bindingsRecv)[USERINFO_GETINFO_RESPONSE_OK] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_UserInfo::Recv_GetInfo_Response_OK));

  (*_bindingsRecv)[USERINFO_GETINFO_RESPONSE_NOK_INVALIDUSER] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_UserInfo::Recv_GetInfo_Response_NOK_InvalidUser));

  (*_bindingsRecv)[USERINFO_GETAVATAR_RESPONSE_OK] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_UserInfo::Recv_GetAvatar_Response_OK));

  (*_bindingsRecv)[USERINFO_GETAVATAR_RESPONSE_NOK_INVALIDUSER] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_UserInfo::Recv_GetAvatar_Response_NOK_InvalidUser));
}

void    Component_UserInfo::RegisteredRequests()
{
  // SEND requests                                                                                                                                                                                                                           
  (*_registeredRequests)[USERINFO_GETINFO_REQUEST] =
    new Request(USERINFO_GETINFO_REQUEST, SEND, "GETINFO_REQUEST", RETRY);

  (*_registeredRequests)[USERINFO_GETAVATAR_REQUEST] =
    new Request(USERINFO_GETAVATAR_REQUEST, SEND, "GETAVATAR_REQUEST", RETRY);


  // RECV requests                                                                                                                                                                                                                           
  (*_registeredRequests)[USERINFO_GETINFO_RESPONSE_OK] =
    new Request(USERINFO_GETINFO_RESPONSE_OK, RECV, "GETINFO_RESPONSE_OK", USERINFO_GETINFO_REQUEST);

  (*_registeredRequests)[USERINFO_GETINFO_RESPONSE_NOK_INVALIDUSER] =
    new Request(USERINFO_GETINFO_RESPONSE_NOK_INVALIDUSER, RECV, "GETINFO_RESPONSE_NOK_INVALIDUSER", USERINFO_GETINFO_REQUEST);

  (*_registeredRequests)[USERINFO_GETAVATAR_RESPONSE_OK] =
    new Request(USERINFO_GETAVATAR_RESPONSE_OK, RECV, "GETAVATAR_RESPONSE_OK", USERINFO_GETAVATAR_REQUEST);

  (*_registeredRequests)[USERINFO_GETAVATAR_RESPONSE_NOK_INVALIDUSER] =
    new Request(USERINFO_GETAVATAR_RESPONSE_NOK_INVALIDUSER, RECV, "GETAVATAR_RESPONSE_NOK_INVALIDUSER", USERINFO_GETAVATAR_REQUEST);
}

void    Component_UserInfo::Send_GetInfo_Request(Session *session, field_t clientSessionId)
{
  Packet_v1_UserInfo *packet_v1_userinfo = new Packet_v1_UserInfo(USERINFO_GETINFO_REQUEST);

  packet_v1_userinfo->setClientSessionId(clientSessionId);
  _clientManager->Send(packet_v1_userinfo, session);
}


void    Component_UserInfo::Send_GetAvatar_Request(Session *session, field_t clientSessionId)
{
  Packet_v1_UserInfo *packet_v1_userinfo = new Packet_v1_UserInfo(USERINFO_GETAVATAR_REQUEST);

  packet_v1_userinfo->setClientSessionId(clientSessionId);
  _clientManager->Send(packet_v1_userinfo, session);
}


void    Component_UserInfo::Recv_GetAvatar_Response_OK(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_UserInfo const *packet_v1_userinfo =
    static_cast<Packet_v1_UserInfo const *>(packet_v1);

  field_t clientSessionId = packet_v1_userinfo->getClientSessionId();

  _avatarMap[clientSessionId] = packet_v1_userinfo->getAvatar();
}

void	Component_UserInfo::Recv_GetAvatar_Response_NOK_InvalidUser(Packet_v1 const *, Session *)
{
  std::cerr << "(!) Received Avatar Response NOK Invaliduser" << std::endl;
}

void    Component_UserInfo::Recv_GetInfo_Response_OK(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_UserInfo const *packet_v1_userinfo =
    static_cast<Packet_v1_UserInfo const *>(packet_v1);

  field_t clientSessionId = packet_v1_userinfo->getClientSessionId();

  _userMap[clientSessionId] = packet_v1_userinfo->getUserInfo();
}

void	Component_UserInfo::Recv_GetInfo_Response_NOK_InvalidUser(Packet_v1 const *, Session *)
{
  std::cerr << "(!) Received GetInfo Response NOK Invaliduser" << std::endl;
}

