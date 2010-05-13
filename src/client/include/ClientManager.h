#ifndef __CLIENTMANAGER_H__
#define __CLIENTMANAGER_H__

class ClientManager;

#include <iostream>
#include <boost/asio.hpp>

#include <Manager.h>
#include <Session.h>
#include <Component_Session.h>

class ClientManager : public Manager
{
public:
					ClientManager(boost::asio::io_service &, boost::threadpool::pool &,
						      boost::asio::ip::udp::socket &, boost::asio::ip::udp::endpoint &);
  virtual				~ClientManager();

  virtual void				Manage(Packet *);
  boost::asio::ip::udp::endpoint	&getEndpoint();

private:
  virtual void				Init_Components();
  virtual void				Disconnect(Session *);


protected:
  // core components
  Component_Session			*_session;
  // list of additional optional components

private:
  boost::asio::ip::udp::endpoint	&_remote_endpoint;
};

#endif // ! __CLIENTMANAGER_H__
