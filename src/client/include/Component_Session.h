#ifndef __COMPONENT_SESSION_H__
#define __COMPONENT_SESSION_H__

#include <iostream>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <IComponent.h>
#include <Packet_v1.h>
#include <Packet_v1_Session_AuthRequest.h>

class Component_Session : public IComponent
{
public:
  Component_Session(IComponent::m_packet_bindings &,
		    boost::asio::ip::udp::endpoint &, boost::asio::ip::udp::socket &);
  virtual	~Component_Session();
  virtual void	PacketBindings();
  
  void		Connect(std::string const &, std::string const &);

private:

  void		CallBack_handle_send();
  void		Send(Packet_v1 *);
  void		Recv_AuthResponse_OK(Packet_v1 *);
  void		Recv_AuthResponse_NOK(Packet_v1 *);
  void		Recv_TimeOutTest(Packet_v1 *);
  void		Recv_KeepAlive(Packet_v1 *);
  void		Recv_Disconnected(Packet_v1 *);
  void		Send_AuthRequest();
  void		Send_TimeOutTestRequest();
  void		Send_Disconnect();
  
  m_packet_bindings  &			_packetBindings;
  boost::asio::ip::udp::endpoint &	_remote_endpoint;
  boost::asio::ip::udp::socket &	_socket;
};

#endif // ! __COMPONENT_SESSION_H__
