#ifndef __COMPONENT_JAM_H__
#define __COMPONENT_JAM_H__

class Component_Jam;
#include "audioengine.h"

#include <iostream>
#include <IComponent.h>
#include <Packet_v1.h>
#include <Packet_v1_Jam.h>
#include <ClientManager.h>
#include <Protocol.h>
#include <Protocol_Jam.h>
#include <Session.h>

class Component_Jam : public IComponent
{
 public:

  Component_Jam(ClientManager *);
  virtual	~Component_Jam();

  void		Send_Jam(char const *, field_t);

  void		StartJam(field_t, Room *);
  void		StopJam(field_t);


  void		Connect(Session *);
  void		Disconnect(Session *);

  private:

  virtual void	BindingsRecv();
  virtual void	RegisteredRequests();

  void		Recv_Jam(Packet_v1 const *, Session *);

 private:

  ClientManager	*_clientManager;
  AudioEngine   *_audioEngine;
};

#endif // ! __COMPONENT_JAM_H__
