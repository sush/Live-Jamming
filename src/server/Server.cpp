#include <Server.h>

const std::string	Server::_address = "127.0.0.1";
const int		Server::_port	= 5042;
const int		Server::_poolSize = 1;
const int		updateTime = 1;
const int		treat_delay = 0; //micro seconds

void		Server::Run()
{
  std::cout << "Server started..." << std::endl;
 
  start_receive();
  _io_service->run();
}


void Server::start_receive()
{
  _recv_buffer = new Packet::buffer_t;
  _remote_endpoint = new boost::asio::ip::udp::endpoint;
  _socket->async_receive_from(boost::asio::buffer(*_recv_buffer), *_remote_endpoint,
			      boost::bind(&Server::CallBack_handle_receive, this,
					  boost::asio::placeholders::error,
					  boost::asio::placeholders::bytes_transferred));
}

void	Server::CallBack_handle_receive(boost::system::error_code const & error, std::size_t recv_count)
{
  if (!error || error == boost::asio::error::message_size)
    {
      ////////// THREAD SAFE//////////////////////
      // !!! to implement !!!
      // this lock should have a very high priority for locking
      // the main receiver thread shouldn t be waiting for all thread workers finishing to treat
      // packets
      ///////////////////////////////////////////////////////

      _packetQueue_mutex.lock();
      Packet * p = new Packet(_remote_endpoint, _recv_buffer, recv_count);
      _packetQueue->PushPacket(p);
      _packetQueue_mutex.unlock();

      ////////////////////////////////////////////

      _pool->schedule(boost::bind(&Server::Thread_TreatPacket, this));
      start_receive();
    }
}

void		Server::CallBack_Debug_Print()
{
#ifdef _DEBUG
  std::cout << "[PaquetQueue] packet_no[" << _packetQueue->getPacketCount() << "] MaxSize = " << _packetQueue->getMaxSize() << ", Size = " << _packetQueue->getSize() << std::endl;
#endif
  _timer->expires_at(_timer->expires_at() + boost::posix_time::seconds(updateTime));
  _timer->async_wait(boost::bind(&Server::CallBack_Debug_Print, this));
}

void		Server::Thread_TreatPacket()
{
  Packet	*packet;

  ///////////// THREAD SAFE ///////////////////////
  _packetQueue_mutex.lock();
  packet = _packetQueue->PopPacket();
  _packetQueue_mutex.unlock();
  ////////////////////////////////////////////////

  //        packet->Print();
  _serverManager->Manage(packet);
  ////////////////////////// WAIT //////////////////
  usleep(treat_delay); // wait <treat_delay> to fake for delay introduced by treatment
  ////////////////////////// WAIT //////////////////
}


void		Server::Init(int argc, char *argv[])
{
  _argc = argc;
  _argv = argv;

  _config = new Config(argc, argv);

  _io_service = new boost::asio::io_service;
  _local_endpoint = new boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), _port);
 
  _socket = new boost::asio::ip::udp::socket (*_io_service);
  _socket->open(boost::asio::ip::udp::v4());
  _socket->bind(*_local_endpoint);
  _packetQueue = new PacketQueue;

  _timer = new boost::asio::deadline_timer(*_io_service, boost::posix_time::seconds(updateTime));
  _timer->async_wait(boost::bind(&Server::CallBack_Debug_Print, this));
  _pool = new boost::threadpool::pool(_poolSize);
  _serverManager = new ServerManager(*_io_service, *_pool);
}
