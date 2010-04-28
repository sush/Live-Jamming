#ifndef __ICOMPONENT_H__
#define __ICOMPONENT_H__

class IComponent;
class ServerManager;
class ClientManager;

#include <iostream>
#include <map>
#include <Protocol.h>
#include <Packet_v1.h>

class IComponent
{
 public:
  typedef void	(IComponent::*pMethod)(Packet_v1 *);
  typedef struct
  {
    IComponent *	instance;
    pMethod		method;
  }PacketBind;
  typedef std::map<field_t, PacketBind>		m_packet_bindings;
  typedef m_packet_bindings::iterator		m_packet_bindings_it;
  typedef m_packet_bindings::const_iterator	m_packet_bindings_cit;

  // this is just to indicate that you have to redefine a constructor and 
  // use serverManager in the server and
  //     clientManager in the client
  // in order to be able to send and/or schedule task for threadpools
  IComponent(ServerManager *) {};
  IComponent(ClientManager *) {};

  virtual ~IComponent() {};
  virtual void	PacketBindings() = 0;
};

#include <ServerManager.h>
#include <ClientManager.h>


#endif // ! __ICOMPONENT_H__

