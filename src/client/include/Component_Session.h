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
  void		Connect(std::string const &, std::string const &);
  bool		IsLogged() const;

private:

  void		CallBack_handle_send() const;
  void		Send(Packet_v1 *) const;
  void		Send(proto_v1_packet_type) const;

  void		Recv_AuthResponse_OK(Packet_v1 *);
  void		Recv_AuthResponse_NOK(Packet_v1 *);
  void		Recv_TimeOutTest(Packet_v1 *);
  void		Recv_KeepAlive(Packet_v1 *);
  void		Recv_Disconnected(Packet_v1 *);
  void		Send_AuthRequest();
  void		Send_TimeOutTestRequest();
  void		Send_Disconnect();
  void		Send_KeepAlive();
  
  m_packet_bindings  &			_packetBindings;
  ClientManager				*_clientManager;
  bool					_logged;
  field_t				_sessionId;
};

#endif // ! __COMPONENT_SESSION_H__
