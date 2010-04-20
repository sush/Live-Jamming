#ifndef __CLIENTSESSION_H__
#define __CLIENTSESSION_H__

#include <iostream>
#include <boost/asio.hpp>
#include <boost/threadpool.hpp>
#include <boost/array.hpp>

#include <Packet.h>

class ClientSession
{
public:
  ClientSession(boost::asio::io_service &, boost::threadpool::pool &,
		boost::asio::ip::udp::socket &, boost::asio::ip::udp::endpoint &);
  virtual	~ClientSession();
  void		Manage(Packet *);


private:
  void		Session_AuthResponse();
  void		Session_TimeOutTestRequest();
  void		Session_TimeOutTestResponse();
  void		Session_Disconnect();
  void		CallBack_handle_send();
  void		Client_AuthRequest();

  boost::asio::io_service &		_io_service;
  boost::threadpool::pool &		_pool;
  boost::asio::ip::udp::socket &	_socket;
  unsigned short int			_sessionId;
  std::string				_login;
  std::string				_pass;
  unsigned int				_port;
  boost::asio::ip::udp::endpoint	_remote_endpoint;
};


#endif // ! __CLIENTSESSION_H__

