#ifndef __COMPONENT_ROOM_H__
#define __COMPONENT_ROOM_H__

class Component_Room;

#include <iostream>
#include <IComponent.h>
#include <Packet_v1.h>
#include <Packet_v1_Room.h>
#include <ClientManager.h>
#include <Protocol.h>
#include <Protocol_Room.h>
#include <Session.h>

class Component_Room : public IComponent
{
 public:

  Component_Jam(ClientManager *);
  virtual	~Component_Jam();

  virtual void	BindingsRecv();
  virtual void	RegisteredRequests();

 private:



 private:

  ClientManager	*_clientManager;
};

#endif // ! __COMPONENT_ROOM_H__
