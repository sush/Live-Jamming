#include <Component_Room.h>
#include <Bind_recv.h>

Component_Room::Component_Room(ClientManager *clientManager)
  : IComponent(ROOM_COMPONENTID), _clientManager(clientManager)
{}

Component_Room::~Component_Room() {}

void	Component_Room::BindingsRecv()
{}

void	Component_Room::RegisteredRequests()
{}

void	Component_Room::Connect(Session *)
{}

void	Component_Room::Disconnect(Session *)
{}
