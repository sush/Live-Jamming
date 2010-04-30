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
#include <Packet_v1_Session_AuthRequest.h>
#include <ClientManager.h>

class Component_Session : public IComponent
{
public:
  Component_Session(IComponent::m_packet_bindings &, ClientManager *);
  virtual	~Component_Session();
  virtual void	PacketBindings();
  
  field_t	getSessionId() const;
  ClientManager	&getClientManager();
  void		Connect(std::string const &, std::string const &);
  bool		IsLogged() const;

private:

  void		Recv_AuthResponse(Packet_v1 *);
  void		Recv_TimeOutTest(Packet_v1 *);
  void		Recv_KeepAlive(Packet_v1 *);
  void		Recv_Disconnected(Packet_v1 *);
  void		Send_AuthRequest();
  void		Send_TimeOutTestRequest();
  void		Send_Disconnect();
  void		Send_KeepAlive();
  void		CallBack_AuthRequest_timeout(boost::system::error_code const &);
  
  m_packet_bindings  &			_packetBindings;
  ClientManager				*_clientManager;
  bool					_logged;
  field_t				_sessionId;
  boost::asio::deadline_timer		*_authRequest_timeout;
};

#endif // ! __COMPONENT_SESSION_H__
