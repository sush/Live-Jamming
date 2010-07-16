#ifndef __COMPONENT_JAM_H__
#define __COMPONENT_JAM_H__

class Component_Jam;

#include <iostream>
#include <IComponent.h>
#include <Packet_v1.h>
#include <Packet_v1_Jam.h>
#include <ClientManager.h>
#include <Protocol.h>
#include <Protocol_Jam.h>
#include <Session.h>
#include <Jam.h>

class Component_Jam : public IComponent
{
 public:

  Component_Jam(ClientManager *);
  virtual	~Component_Jam();

  void		Send_Jam(Session *, char const *, field_t);

  private:

  virtual void	BindingsRecv();
  virtual void	RegisteredRequests();

  void		Recv_Jam(Packet_v1 const *, Session *);

  void		StartJam(field_t, Room *);
  void		StopJam(field_t);

  void		Connect(Session *);
  void		Disconnect(Session *);

 private:

  ClientManager	*_clientManager;
  Jam		*_jam;
};

#endif // ! __COMPONENT_JAM_H__
