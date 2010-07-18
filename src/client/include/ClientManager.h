#ifndef __CLIENTMANAGER_H__
#define __CLIENTMANAGER_H__

class ClientManager;
class Component_Session;
class Component_Channel;
class Component_Friend;
class Component_Room;
class Component_Jam;
class Session;

#include <iostream>
#include <boost/asio.hpp>

#include <Manager.h>

class ClientManager : public Manager
{
public:
					ClientManager(boost::asio::io_service &, boost::threadpool::pool &,
						      boost::asio::ip::udp::socket &, boost::asio::ip::udp::endpoint &);
  virtual				~ClientManager();

  virtual void				Manage(Packet *);
  boost::asio::ip::udp::endpoint	&getEndpoint();
  virtual void				Disconnect(Session *);
  virtual void				Connect(std::string const &, std::string const &);
  virtual void				Connect(Session *) {} // pure virtual must be implemented
  Component_Jam				*getComponentJam();

private:
  virtual void				Init_Components();


protected:
  // core components
  Component_Session			*_session;
  Component_Channel			*_channel;
  Component_Friend			*_friend;
  Component_Room			*_room;
  Component_Jam				*_jam;
  // list of additional optional components

private:
  boost::asio::ip::udp::endpoint	&_remote_endpoint;
};

#endif // ! __CLIENTMANAGER_H__
