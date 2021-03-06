#ifndef __CLIENT_H__
#define __CLIENT_H__

class Client;

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
#include <Config.h>
#include <mainwindow.h>
#include <proxy.h>
#include <ClientManager.h>

class Client : public Singleton<Client>
{
  friend class Singleton<Client>;

public:
  void					Run();
  void					Init(int, char *[]);
  void					Connect(std::string const &, std::string const &, std::string const &, int);
  void					Disconnect();
    
private:
  void					BindToLocalPort();
  void					Thread_TreatPacket();
  void					start_receive();
  void					CallBack_handle_receive(boost::system::error_code const &, std::size_t);
  void					CallBack_Debug_Print();
  void					CallBack_handle_send();

  int					_argc;
  char					**_argv;
  static const std::string		_address;
  static int				_port;
  static int				_connect_port;
  static int				_poolSize;

  boost::mutex				_packetQueue_mutex;

  boost::asio::io_service		*_io_service;
  boost::threadpool::pool		*_pool;

  boost::asio::deadline_timer		*_timer;
  boost::asio::ip::udp::socket		*_socket;
  boost::asio::ip::udp::endpoint	*_local_endpoint;
  boost::asio::ip::udp::endpoint	*_remote_endpoint;
  Packet::buffer_t			*_recv_buffer;
  PacketQueue				*_packetQueue;
  Config				*_config;
  //  ClientManager				*_clientManager;
  ClientManager				*_clientManager;
  std::size_t				_debug_print_packet;
};

#endif // ! __CLIENT_H__ 
