#include <Client.h>

//const char		connect_address[] = "127.0.0.1";
const char		connect_address[] = "88.191.94.150";

const int		Client::_connect_port	= 5042;
int			Client::_port	= _connect_port;
int			Client::_poolSize = 1;
const int		updateTime = 1;
const int		treat_delay = 0; //micro seconds

void		Client::Run()
{
  std::cout << "Client started..." << std::endl;
 
  start_receive();
  _io_service->run();
}


void Client::start_receive()
{
  _recv_buffer = new Packet::buffer_t;
  _remote_endpoint = new boost::asio::ip::udp::endpoint;
  _socket->async_receive_from(boost::asio::buffer(*_recv_buffer), *_remote_endpoint,
			      boost::bind(&Client::CallBack_handle_receive, this,
					  boost::asio::placeholders::error,
					  boost::asio::placeholders::bytes_transferred));
}

void	Client::CallBack_handle_receive(boost::system::error_code const & error, std::size_t recv_count)
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
      _packetQueue->PushPacket(new Packet(_remote_endpoint, _recv_buffer, recv_count));
      _packetQueue_mutex.unlock();

      ////////////////////////////////////////////

      _pool->schedule(boost::bind(&Client::Thread_TreatPacket, this));
      start_receive();
    }
}

void		Client::CallBack_Debug_Print()
{
#ifdef _DEBUG
  std::cout << "[PaquetQueue] packet_no[" << _packetQueue->getPacketCount() << "] MaxSize = " << _packetQueue->getMaxSize() << ", Size = " << _packetQueue->getSize() << std::endl;
#endif
  _timer->expires_at(_timer->expires_at() + boost::posix_time::seconds(updateTime));
  _timer->async_wait(boost::bind(&Client::CallBack_Debug_Print, this));
}

void		Client::Thread_TreatPacket()
{
  Packet	*packet;

  ///////////// THREAD SAFE ///////////////////////
  _packetQueue_mutex.lock();
  packet = _packetQueue->PopPacket();
  _packetQueue_mutex.unlock();
  ////////////////////////////////////////////////

  //        packet->Print();
  _clientManager->Manage(packet);
  ////////////////////////// WAIT //////////////////
  usleep(treat_delay); // wait <treat_delay> to fake for delay introduced by treatment
  ////////////////////////// WAIT //////////////////
}

void		Client::CallBack_handle_send()
{
}

void		Client::BindToLocalPort()
{
  do {
    try {
      _local_endpoint = new boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), _port);
      _socket->bind(*_local_endpoint);
    }
    catch (std::exception e)
      {
	++_port; // try to bind to next local port until one is available
	delete _local_endpoint;
	_local_endpoint = 0;
      }
  }
  while (!_local_endpoint);
}

void		Client::Init(int argc, char *argv[])
{
  _argc = argc;
  _argv = argv;
  _io_service = new boost::asio::io_service;
  _remote_endpoint = new boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(connect_address), Client::_connect_port);

  _socket = new boost::asio::ip::udp::socket (*_io_service);
  _socket->open(boost::asio::ip::udp::v4());
  BindToLocalPort();
  _packetQueue = new PacketQueue;

  _timer = new boost::asio::deadline_timer(*_io_service, boost::posix_time::seconds(updateTime));
  _timer->async_wait(boost::bind(&Client::CallBack_Debug_Print, this));
  _pool = new boost::threadpool::pool(_poolSize);
  _clientManager = new ClientManager(*_io_service, *_pool, *_socket, *_remote_endpoint);
}
