#include <Server.h>

namespace lj
{

  const std::string	Server::_address = "192.168.0.13";
  const int		Server::_port	= 5042;
  const int		Server::_poolSize = 8;

  void		Server::Run()
  {
    std::cout << "Server started..." << std::endl;
 
    _pool = new boost::threadpool::pool(_poolSize);
    start_receive();
    _io_service.run();
  }


  void Server::start_receive()
  {
    _recv_buffer = new Packet::buffer_t;
    _socket->async_receive_from(boost::asio::buffer(*_recv_buffer), _remote_endpoint,
				boost::bind(&Server::CallBack_handle_receive, this,
					    boost::asio::placeholders::error,
					    boost::asio::placeholders::bytes_transferred));
  }

  void	Server::CallBack_handle_receive(boost::system::error_code const & error, std::size_t recv_count)
  {
    if (!error || error == boost::asio::error::message_size)
      {
	////////// THREAD SAFE//////////////////////
	_push_mutex.lock();

	std::cout << "receive" << std::endl;
	_packetQueue->PushPacket(new Packet(_recv_buffer, recv_count));
	_pool->schedule(boost::bind(&Server::Thread_task, this));
	start_receive();

	_push_mutex.unlock();
	////////////////////////////////////////////
      }
  }

  void		Server::Thread_task()
  {
    ///////////// THREAD SAFE ///////////////////////
    _pop_mutex.lock();
    Packet	*packet = _packetQueue->PopPacket();
    //    packet->Print();
    std::cout << "Queue max Size = " << _packetQueue->getMaxSize() << std::endl;
    delete packet;
    _pop_mutex.unlock();
    ////////////////////////////////////////////////
  }

  void		Server::Init(int argc, char *argv[])
  {
    _argc = argc;
    _argv = argv;
    _local_endpoint = new boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(_address.c_str()), _port);
 
    _socket = new boost::asio::ip::udp::socket (_io_service);
    _socket->open(boost::asio::ip::udp::v4());
    _socket->bind(*_local_endpoint);
    _packetQueue = new PacketQueue;
  }

}
