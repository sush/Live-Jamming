#ifndef __ICOMPONENT_H__
#define __ICOMPONENT_H__

class IComponent;
class Bind_recv;
class Session;
class Manager;
class Packet_v1;

#include <iostream>
#include <map>
#include <boost/asio.hpp>
#include <Protocol.h>
//#include <Session.h>
//#include <Bind_send.h>

class IComponent
{
 public:
  typedef void	(IComponent::*pMethod)(Packet_v1 const *, Session *);

  typedef std::map<proto_v1_packet_type, Bind_recv *>	m_bindings_recv;
  typedef m_bindings_recv::iterator			m_bindings_recv_it;
  typedef m_bindings_recv::const_iterator		m_bindings_recv_cit;

  //  typedef std::map<proto_v1_packet_type, Bind_send *>	m_bindings_send;
  //  typedef m_bindings_send::iterator		m_bindings_send_it;
  //  typedef m_bindings_send::const_iterator	m_bindings_send_cit;


  // this is just to indicate that you have to redefine a constructor and 
  // use serverManager in the server and
  //     clientManager in the client
  // in order to be able to send and/or schedule task for threadpools
  IComponent(Manager *) {}

  virtual ~IComponent() {};
  virtual void	BindingsRecv() = 0;
  //  virtual void	Bindings_send() = 0;
};

#include <Bind_recv.h>

#endif // ! __ICOMPONENT_H__

