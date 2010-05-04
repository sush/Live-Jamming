#ifndef __SERVER_MANAGER_H__
#define __SERVER_MANAGER_H__

class ServerManager;

#include <iostream>

#include <Manager.h>
#include <Session.h>
#include <Component_SessionManager.h>

class ServerManager : public Manager
{
public:

  ServerManager(boost::asio::io_service &, boost::threadpool::pool &, boost::asio::ip::udp::socket &);
  virtual	~ServerManager();

  virtual void		Manage(Packet *);
  unsigned int		CountActiveSessions() const;

private:
  virtual void		Init_Components();
  virtual void		Disconnect(Session *);

  
private:
  // core components
  Component_SessionManager		*_sessionManager;
  // list of additional optional components
};

#endif // ! __SERVER_MANAGER_H__
