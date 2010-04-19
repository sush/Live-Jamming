#ifndef __SERVER_H__
#define __SERVER_H__

class Server;

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/threadpool.hpp>

#include <iostream>
#include <Packet.h>
#include <PacketQueue.h>
#include <Singleton.h>
#include <SessionManager.h>
#include <Config.h>


class Server : public Singleton<Server>
{
  friend class Singleton<Server>;

 public:
  void			Run();
  void			Init(int, char *[]);
    
 private:
  void			Thread_TreatPacket();
  void			start_receive();
  void			CallBack_handle_receive(boost::system::error_code const &, std::size_t);
  void			CallBack_Debug_Print();

  int				_argc;
  char			**_argv;
  static const std::string	_address;
  static const int		_port;
  static const int		_poolSize;

  boost::mutex			_packetQueue_mutex;

  boost::asio::io_service		*_io_service;
  boost::threadpool::pool		*_pool;

  boost::asio::deadline_timer		*_timer;
  boost::asio::ip::udp::socket	*_socket;
  boost::asio::ip::udp::endpoint	*_local_endpoint;
  boost::asio::ip::udp::endpoint	*_remote_endpoint;
  Packet::buffer_t			*_recv_buffer;
  PacketQueue				*_packetQueue;
  SessionManager			*_sessionManager;
  Config				*_config;
};

#endif // ! __SERVER_H__ 
