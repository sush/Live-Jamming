#ifndef __SERVER_MANAGER_H__
#define __SERVER_MANAGER_H__

class ServerManager;

#include <iostream>

#include <Manager.h>
#include <Session.h>
#include <Component_SessionManager.h>
#include <Component_ChannelManager.h>

class ServerManager : public Manager
{
public:

  ServerManager(boost::asio::io_service &, boost::threadpool::pool &, boost::asio::ip::udp::socket &);
  virtual	~ServerManager();

  virtual void		Manage(Packet *);
  unsigned int		CountActiveSessions() const;
  virtual void		Disconnect(Session *);
  

private:
  virtual void		Init_Components();

  
private:
  // core components
  Component_SessionManager		*_sessionManager;
  Component_ChannelManager		*_channelManager;
  // list of additional optional components
};

#endif // ! __SERVER_MANAGER_H__
