#include <Component_RoomManager.h>

Component_RoomManager::Component_RoomManager(IComponent::m_bindings_recv & bindingsRecv, ServerManager *serverManager)
  :IComponent(clientManager), _bindingsRecv(bindingsRecv), _serverManager(serverManager) 
{
  BindingsRecv();
}

Component_RoomManager::~Component_RoomManager() {}

void	Component_RoomManager::BindingsRecv()
{
  _bindingsRecv[ROOM_JOIN] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_RoomManager::Recv_Join));

  _bindingsRecv[ROOM_LEAVE] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_RoomManager::Recv_Leave));

  _bindingsRecv[ROOM_KICK] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_RoomManager::Recv_Kick));

  _bindingsRecv[ROOM_INVITATION] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_RoomManager::Recv_Invitation));

  _bindingsRecv[ROOM_UPDATE_SETING] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_RoomManager::Recv_UpdateSetting));
}

void	Component_RoomManager::Recv_Join(Packet_v1 *packet_v1, Session *session)
{
}

void	Component_RoomManager::Recv_Leave(Packet_v1 *packet_v1, Session *session)
{
}

void	Component_RoomManager::Recv_Kick(Packet_v1 *packet_v1, Session *session)
{
}

void	Component_RoomManager::Recv_Invitation(Packet_v1 *packet_v1, Session *session)
{
}

void	Component_RoomManager::Recv_UpdateSetting(Packet_v1 *packet_v1, Session *session)
{
}

void	Component_RoomManager::Send_Joined_OK(Session *session)
{
}

void	Component_RoomManager::Send_Joined_NOK_ALREADYIN(Session *session)
{
}

void	Component_RoomManager::Send_Leaved_OK(Session *session)
{
}

void	Component_RoomManager::Send_Leaved_NOK_NOTIN(Session *session)
{
}

void	Component_RoomManager::Send_Kick_OK(Session *session)
{
}

void	Component_RoomManager::Send_Kick_NOK_NOTIN(Session *session)
{
}

void	Component_RoomManager::Send_Invitation_OK(Session *session)
{
}

void	Component_RoomManager::Send_Invitation_NOK_ALREADYIN(Session *session)
{
}
