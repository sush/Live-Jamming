#ifndef __CLIENTSESSION_H__
#define __CLIENTSESSION_H__

#include <iostream>
#include <map>
#include <boost/asio.hpp>
#include <boost/threadpool.hpp>
#include <boost/array.hpp>

#include <Packet.h>
#include <Packet_v1.h>
#include <Protocol.h>

class ClientSession
{
public:
  ClientSession(boost::asio::io_service &, boost::threadpool::pool &,
		boost::asio::ip::udp::socket &, boost::asio::ip::udp::endpoint &);
  virtual	~ClientSession();
  void		Manage(Packet *);


private:
  typedef void (ClientSession::*pMethod)(Packet_v1 *);
  typedef std::map<field_t, pMethod>			m_packet_binding;
  typedef m_packet_binding::iterator			m_packet_binding_it;
  typedef m_packet_binding::const_iterator		m_packet_binding_cit;

  void		Session_AuthResponse();
  void		Session_TimeOutTestRequest();
  void		Session_TimeOutTestResponse();
  void		Session_Disconnect();
  void		CallBack_handle_send();
  void		Client_AuthRequest();
  void		Init_PacketBinding();
  void		Packet_AuthRespond_OK(Packet_v1 *);
  void		Packet_AuthRespond_NOK(Packet_v1 *);
  void		Packet_TimeOut(Packet_v1 *);
  void		Packet_KeepAlive(Packet_v1 *);
  void		Packet_Disconnected(Packet_v1 *);

  boost::asio::io_service &		_io_service;
  boost::threadpool::pool &		_pool;
  boost::asio::ip::udp::socket &	_socket;
  unsigned short int			_sessionId;
  std::string				_login;
  std::string				_pass;
  unsigned int				_port;
  boost::asio::ip::udp::endpoint	_remote_endpoint;
  m_packet_binding			_packetBinding;
};


#endif // ! __CLIENTSESSION_H__

