#ifndef __COMPONENT_SESSION_H__
#define __COMPONENT_SESSION_H__

class Component_Session;

#include <iostream>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <IComponent.h>
#include <Protocol.h>
#include <Packet_v1.h>
#include <Packet_v1_Session.h>
#include <ClientManager.h>
#include <Session.h>
#include <mainwindow.h>

class ClientManager;

class Component_Session : public IComponent
{
public:
  Component_Session(ClientManager *);
  virtual	~Component_Session();
  virtual void	BindingsRecv();
  virtual void	RegisteredRequests();
  
  field_t	getSessionId() const;
  ClientManager	&getClientManager();
  Session	*getSession();
  void		Connect(std::string const &, std::string const &);
  bool		IsLogged() const; // not implemented yet (since on session creation always auth ...
  void		Disconnect();

private:

  void		Recv_AuthResponse(Packet_v1 const *, Session *);
  void		Recv_TimeOutTest(Packet_v1 const *, Session *);
  void		Recv_KeepAlive(Packet_v1 const *, Session *);
  void		Recv_Disconnected(Packet_v1 const *, Session *);
  void		Send_AuthRequest(std::string const &, std::string const &);
  void		Send_TimeOutTestRequest();
  void		Send_Disconnect();
  void		Send_KeepAlive();
  void		Recv_Friend_Leaved(Packet_v1 const *, Session *);
  void		Recv_Friend_Joined(Packet_v1 const *, Session *);

  void		Send_Add_Friend(char const *);
  void		Send_Del_Friend(char const *);

  void		Recv_Add_Friend_OK(Packet_v1 const *, Session *);
  void		Recv_Add_Friend_NOK(Packet_v1 const *, Session *);

  void		Recv_Del_Friend_OK(Packet_v1 const *, Session *);
  void		Recv_Del_Friend_NOK(Packet_v1 const *, Session *);

  void		CallBack_AuthRequest_timeout(boost::system::error_code const &);
  
  ClientManager				*_clientManager;
  bool					_logged;
public:
  Session				*_session;

};

#endif // ! __COMPONENT_SESSION_H__
