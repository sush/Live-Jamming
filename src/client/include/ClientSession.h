#ifndef __CLIENTSESSION_H__
#define __CLIENTSESSION_H__

#include <iostream>
#include <map>
#include <boost/asio.hpp>
#include <boost/threadpool.hpp>
#include <boost/array.hpp>

#include <Protocol.h>
#include <IComponent.h>
#include <Component_Session.h>

class ClientSession
{
public:
  ClientSession(boost::asio::io_service &, boost::threadpool::pool &,
		boost::asio::ip::udp::socket &, boost::asio::ip::udp::endpoint &);
  virtual	~ClientSession();
  void		Manage(Packet *);


private:
  void		Init_Components();

  boost::asio::io_service &		_io_service;
  boost::threadpool::pool &		_pool;
  boost::asio::ip::udp::socket &	_socket;
  boost::asio::ip::udp::endpoint	_remote_endpoint;
  IComponent::m_packet_bindings		_packetBindings;
  // core components
  Component_Session			*_session;
  // list of additional optional components
};


#endif // ! __CLIENTSESSION_H__

