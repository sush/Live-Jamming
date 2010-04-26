#ifndef __SERVER_MANAGER_H__
#define __SERVER_MANAGER_H__

class ServerManager;

#include <iostream>
#include <list>
#include <map>
#include <boost/asio.hpp>
#include <boost/threadpool.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/random.hpp>

#include <Server.h>
#include <Packet_v1.h>
#include <Protocol.h>
#include <IComponent.h>
#include <Component_SessionManager.h>

class ServerManager
{
public:

  ServerManager(boost::asio::io_service &, boost::threadpool::pool &);
  virtual	~ServerManager();

  void		Manage(Packet *);
  void		Init_Components();

private:
  boost::asio::io_service &		_io_service;
  boost::threadpool::pool &		_pool;
  boost::asio::ip::udp::socket *	_socket;
  IComponent::m_packet_bindings		_packetBindings;
  Component_SessionManager		*_sessionManager;
};



#endif // ! __SERVER_MANAGER_H__
