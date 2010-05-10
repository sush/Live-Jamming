#ifndef __COMPONENT_JAM_H__
#define __COMPONENT_JAM_H__

class Component_Jam;

#include <IComponent.h>
#include <Packet_v1.h>
#include <ClientManager.h>
#include <Session.h>
#include <Audio.h>

class Component_Jam : public IComponent
{
 public:

  Component_Jam(IComponent::m_bindings_recv &, ClientManager *);
  virtual               ~Component_Jam();
  virtual void          BindingsRecv();

 private:
  void			Recv_Start(Packet_v1*);
  void			Recv_Output(Packet_v1 *);
  void			Recv_Stop(Packet_v1 *);
  
  void			Send_Input(Packet_v1 *, Session *);)


  m_bindings_recv &     _bindingsRecv;
  ClientManager         *_clientManager;
/*Audio			_audio;*/
};

#endif

