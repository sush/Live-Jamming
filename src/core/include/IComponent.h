#ifndef __ICOMPONENT_H__
#define __ICOMPONENT_H__

class IComponent;
class Bind_recv;
class Session;
//class Manager;
class Packet_v1;

#include <iostream>
#include <map>
#include <boost/asio.hpp>
#include <Protocol.h>
#include <Request.h>
//#include <Session.h>
//#include <Bind_send.h>

class IComponent
{
 public:
  typedef void	(IComponent::*pMethod)(Packet_v1 const *, Session *);

  typedef std::map<field_t, Request *>			m_request;
  typedef m_request::iterator				m_request_it;
  typedef m_request::const_iterator			m_request_cit;

  typedef std::map<field_t, Bind_recv *>		m_bindings_recv;
  typedef m_bindings_recv::iterator			m_bindings_recv_it;
  typedef m_bindings_recv::const_iterator		m_bindings_recv_cit;

  //  typedef std::map<proto_v1_packet_type, Bind_send *>	m_bindings_send;
  //  typedef m_bindings_send::iterator		m_bindings_send_it;
  //  typedef m_bindings_send::const_iterator	m_bindings_send_cit;


  // this is just to indicate that you have to redefine a constructor and 
  // use serverManager in the server and
  //     clientManager in the client
  // in order to be able to send and/or schedule task for threadpools
 IComponent(field_t componentId):_componentId(componentId), _bindingsRecv(0), _registeredRequests(0) {}

  virtual ~IComponent() {};
  virtual void		BindingsRecv() = 0;
  virtual void		RegisteredRequests() = 0;
  //  virtual void	Bindings_send() = 0;
  
  field_t		getComponentId()				{ return _componentId; }
  void			setBindingsRecv(m_bindings_recv & bindingsRecv)	{ _bindingsRecv = &bindingsRecv; }
  void			setRegisteredRequests(m_request & requests)	{ _registeredRequests = &requests; }

protected:
  const field_t		_componentId;
  m_bindings_recv	*_bindingsRecv;
  m_request		*_registeredRequests;
};

#include <Bind_recv.h>

#endif // ! __ICOMPONENT_H__

