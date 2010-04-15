#include <Server.h>

namespace lj
{

  const std::string	Server::_address = "127.0.0.1";
  const int		Server::_port	= 5042;
  const int		Server::_poolSize = 8;
  const int		updateTime = 1;
  const int		treat_delay = 0; //micro seconds

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
	_packetQueue_mutex.lock();
	_packetQueue->PushPacket(new Packet(_recv_buffer, recv_count));
	_packetQueue_mutex.unlock();
	////////////////////////////////////////////

	_pool->schedule(boost::bind(&Server::Thread_task, this));
	start_receive();
      }
  }

  void		Server::Debug_Print()
  {
    std::cout << "[PaquetQueue] packet_no[" << _packetQueue->getPacketCount() << "] MaxSize = " << _packetQueue->getMaxSize() << ", Size = " << _packetQueue->getSize() << std::endl;
    _timer->expires_at(_timer->expires_at() + boost::posix_time::seconds(updateTime));
    _timer->async_wait(boost::bind(&Server::Debug_Print, this));
  }

  void		Server::Thread_task()
  {
    Packet	*packet;

    ///////////// THREAD SAFE ///////////////////////
    _packetQueue_mutex.lock();
    packet = _packetQueue->PopPacket();
    _packetQueue_mutex.unlock();
    ////////////////////////////////////////////////

    //        packet->Print();
    delete packet;
    ////////////////////////// WAIT //////////////////
    usleep(treat_delay); // wait 15ms to fake for delay introduced by treatment
    ////////////////////////// WAIT //////////////////
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

    _timer = new boost::asio::deadline_timer(_io_service, boost::posix_time::seconds(updateTime));
    _timer->async_wait(boost::bind(&Server::Debug_Print, this));
  }

}
