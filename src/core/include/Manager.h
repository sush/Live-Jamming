#ifndef __MANAGER_H__
#define __MANAGER_H__

class Manager;
class Session;

#include <iostream>
#include <list>
#include <map>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/threadpool.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/random.hpp>

#include <Packet_v1.h>
#include <Protocol.h>
#include <IComponent.h>

class Manager
{
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

  void		Send(Packet_v1 *, Session *, bool) const;
  void		Send(proto_v1_packet_type, Session *, bool) const;
  // this is useful for sending without being authentificated
  void		Send(Packet_v1 *, boost::asio::ip::udp::endpoint &) const;
  void		Send_TimeOut(Session *, Packet_v1 *, boost::system::error_code);
  void		CallBack_TimeOutTest(Session *, boost::system::error_code const &);
  void		CallBack_TimeOutOccurred(Session *, boost::system::error_code const &);

protected:
  virtual void		Init_Components() = 0;
  virtual void		Disconnect(Session *) = 0;

  void		CallBack_handle_send(Packet_v1 *) const;
  void		Send_TimeOutTest(Session *);

  // this is needed cuz boost::bind has trouble when binding overloaded functions
  void		Send_bind(Packet_v1 *, Session *, bool) const;
  
  
protected:
  // these should be made part of options
  unsigned int				_retryDelay;
  unsigned int				_timeOutTestDelay;
  unsigned int				_timeOutOccurredDelay;
  
  boost::asio::io_service &		_io_service;
  boost::threadpool::pool &		_pool;
  boost::asio::ip::udp::socket &	_socket;
  IComponent::m_bindings_recv		_bindingsRecv;
};

#include <Session.h>

#endif // ! __MANAGER_H__
