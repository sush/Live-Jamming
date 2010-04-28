#ifndef __CLIENTMANAGER_H__
#define __CLIENTMANAGER_H__

class ClientManager;

#include <iostream>
#include <map>
#include <boost/asio.hpp>
#include <boost/threadpool.hpp>
#include <boost/array.hpp>

#include <Protocol.h>
#include <IComponent.h>
#include <Component_Session.h>

class ClientManager
{
public:
  ClientManager(boost::asio::io_service &, boost::threadpool::pool &,
		boost::asio::ip::udp::socket &, boost::asio::ip::udp::endpoint &);
  virtual	~ClientManager();
  void		Manage(Packet *);

  boost::asio::ip::udp::endpoint &	getEndpoint();

  void					CallBack_handle_send(Packet_v1 *) const;
  void					Send(proto_v1_packet_type) const;
  void					Send(Packet_v1 *) const;

private:
  void		Init_Components();

  boost::asio::io_service &		_io_service;
  boost::threadpool::pool &		_pool;
  boost::asio::ip::udp::socket &	_socket;
  boost::asio::ip::udp::endpoint &	_remote_endpoint;
  IComponent::m_packet_bindings		_packetBindings;
  // core components
  Component_Session			*_session;
  // list of additional optional components
};


#endif // ! __CLIENTMANAGER_H__

