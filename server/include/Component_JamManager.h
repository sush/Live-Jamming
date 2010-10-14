#ifndef __COMPONENT_JAMMANAGER_H__
#define __COMPONENT_JAMMANAGER_H__

class Component_JamManager;

#include <map>
#include <Server.h>
#include <IComponent.h>
#include <Protocol.h>
#include <Protocol_Jam.h>
#include <Packet_v1.h>
#include <Packet_v1_Jam.h>
#include <ServerManager.h>
#include <Session.h>
#include <Room.h>
#include <Jam.h>

class Component_JamManager : public IComponent
{
  friend class Session;
  friend class ServerManager;

 public:

  Component_JamManager(ServerManager *);
  virtual	~Component_JamManager();

  void		StartJam(field_t, Room*);
  void		StopJam(field_t);

 private:

  virtual void	BindingsRecv();
  virtual void	RegisteredRequests();

  void		Send_Jam(Session *, char const *, field_t);
  void		Recv_Jam(Packet_v1 const *, Session *);

  void		Connect(Session *);
  void		Disconnect(Session *);

 private:

  typedef std::map<field_t, Jam *> m_jam;
  m_jam		*_jamMap;
  ServerManager *_serverManager;
};

#endif // ! __COMPONENT_JAMMANAGER_H__
