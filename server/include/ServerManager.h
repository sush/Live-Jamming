#ifndef __SERVER_MANAGER_H__
#define __SERVER_MANAGER_H__

class ServerManager;
class Manager;
class Session;
class Component_SessionManager;
class Component_ChannelManager;
class Component_FriendManager;
class Component_RoomManager;
class Component_JamManager;

#include <iostream>
#include <map>

#include <Config.h>
#include <Manager.h>
#include <Packet.h>

class ServerManager : public Manager
{
public:
  typedef std::map<field_t, Session *>		m_Session;
  typedef m_Session::iterator			m_Session_it;
  typedef m_Session::const_iterator		m_Session_cit;

  ServerManager(boost::asio::io_service &, boost::threadpool::pool &, boost::asio::ip::udp::socket &, Config *);
  virtual	~ServerManager();

  virtual void				Manage(Packet *);
  unsigned int				CountActiveSessions() const;
  virtual void				Disconnect(Session *);
  virtual void				Connect(Session *);
  m_Session &				getSessionMap();
  Component_JamManager			*getComponentJam();
  Component_SessionManager		*getComponentSession();
  Config				*getConfig();

private:
  virtual void		Init_Components();

private:
  // core components
  Component_SessionManager		*_sessionManager;
  Component_ChannelManager		*_channelManager;
  Component_FriendManager		*_friendManager;
  Component_RoomManager			*_roomManager;
  Component_JamManager			*_jamManager;
  // list of additional optional components
  m_Session				_sessionMap;
  Config				*_config;
};

#endif // ! __SERVER_MANAGER_H__
