#ifndef __MANAGER_H__
#define __MANAGER_H__

class Manager;
class Packet_v1;

#include <iostream>
#include <list>
#include <map>


typedef std::map<std::string, std::string>	m_userinfo;
typedef m_userinfo::iterator			m_userinfo_it;
typedef m_userinfo::const_iterator		m_userinfo_cit;
typedef std::pair<std::string, std::string>	m_userinfo_pair;

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/threadpool.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/random.hpp>

#include <IComponent.h>
#include <Protocol.h>
#include <Packet.h>


class Manager
{
private:
  typedef struct
  {
    IComponent::m_bindings_recv	_bindingsRecv;
    IComponent::m_request	_registeredRequests;
  }component_binding;

  typedef std::map<field_t, component_binding*>	m_component_bindings;
  typedef m_component_bindings::iterator	m_component_bindings_it;
  typedef m_component_bindings::const_iterator	m_component_bindings_cit;

  m_component_bindings		_componentBindings;

public:
  Manager(boost::asio::io_service &, boost::threadpool::pool &, boost::asio::ip::udp::socket &);
  virtual	~Manager();

  boost::threadpool::pool &		getPool();
  boost::asio::io_service &		getIO();

  // temporary until linked with option
  unsigned int				getRetryDelay() const;
  unsigned int				getTimeOutTestDelay() const;
  unsigned int				getTimeOutOccurredDelay() const;

  virtual void		Manage(Packet *) = 0;

  void		Send(Packet_v1 *, Session *) const;
  void		Send(field_t, field_t, Session *) const;
  // this is useful for sending without being authentificated
  void		Send(field_t, field_t, boost::asio::ip::udp::endpoint const &) const;
  void		Send(Packet_v1 *, boost::asio::ip::udp::endpoint const &) const;

  void		CallBack_Send_TimeOut(Session *, Packet_v1 *, boost::system::error_code);
  void		CallBack_TimeOutTest(Session *, boost::system::error_code const &);
  void		CallBack_TimeOutOccurred(Session *, boost::system::error_code const &);

  // a simple method to return string name of a request
  std::string const &			getRegisteredRequestName(field_t, field_t) const;

  Packet_v1	*Cond_new_Packet(boost::asio::ip::udp::endpoint &, Packet::buffer_t &, int) const;
  Packet_v1	*Cond_new_Packet(int, int) const;

protected:
  virtual void		Init_Components() = 0;
  virtual void		Disconnect(Session *) = 0;
  virtual void		Connect(Session *) = 0;

  void		CallBack_handle_send(Packet_v1 *) const;
  void		Send_TimeOutTest(Session *);

  // this is needed cuz boost::bind has trouble when binding overloaded functions
  void		Send_bind(Packet_v1 *, Session *) const;

protected:
  IComponent::m_bindings_recv const 	&getBindingsRecv(field_t) const;
  IComponent::m_request const		&getRegisteredRequests(field_t) const;

  void					RegisterComponent(IComponent *);
  bool					IsRegisteredComponent(field_t) const;
  bool					IsRegisteredRequest(field_t, field_t) const;
  bool					IsBindRecv(field_t, field_t) const;
  Bind_recv const			&getBindRecv(field_t, field_t) const;
  Request const				&getRegisteredRequest(field_t, field_t) const;

protected:
  // these should be made part of options
  unsigned int				_retryDelay;
  unsigned int				_timeOutTestDelay;
  unsigned int				_timeOutOccurredDelay;
  
  boost::asio::io_service &		_io_service;
  boost::threadpool::pool &		_pool;
  boost::asio::ip::udp::socket &	_socket;
};

#include <Session.h>

#endif // ! __MANAGER_H__
