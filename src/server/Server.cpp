#include <Server.h>
#include <stdexcept>
#include <Packet_v1.h>
#include <Color.h>
#include <Time.h>

// unix dependent, do analogue treatment on windows
#include <signal.h>

const std::string	Server::_address = "127.0.0.1";
const int		Server::_port	= 5042;
const int		Server::_poolSize = 1;
const int		updateTime = 1;
const int		treat_delay = 0; //micro seconds


void sighandler(int sig)
{
  std::cout<< "Signal " << sig << " caught..." << std::endl;
  Server::Stop();
}

void		Server::Stop()
{
  Server	*server=Server::getInstance();
  server->_io_service->stop();
}

void		Server::Run()
{
  std::cout << "* ";
  Time::Print();
  std::cout << " Server started..." << std::endl;
  
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
      // MOVED THE LOCK INSIDE CLASS: ADD INT PARAMETER FOR LOCKING PRIORITY

      try {
	Packet * p = reinterpret_cast<Packet *>(_serverManager->Cond_new_Packet(*_remote_endpoint, *_recv_buffer, recv_count));
	_packetQueue->PushPacket(p);
	_pool->schedule(boost::bind(&Server::Thread_TreatPacket, this));
      }
      catch (std::runtime_error &e)
	{
	  std::cout << e.what() << ":" << Packet_v1::peekComponentId(*_recv_buffer) << std::endl;
	  delete _recv_buffer;
	  _recv_buffer = 0;
	}
	start_receive();
      ////////////////////////////////////////////
    }
}

void		Server::CallBack_Debug_Print()
{

#ifdef _DEBUG
  if (_debug_print_session != _serverManager->CountActiveSessions() ||
      _debug_print_packet != _packetQueue->getPacketCount())
    {
      std::cerr << Time::getTime()
		<< "[ActiveSessions = " << _serverManager->CountActiveSessions() << "] "
		<< "[PaquetQueue] packet_no[" << _packetQueue->getPacketCount()
		<< "] MaxSize = " << _packetQueue->getMaxSize()
		<< ", Size = " << _packetQueue->getSize() << std::endl;
    }
#endif
  _debug_print_packet = _packetQueue->getPacketCount();
  _debug_print_session = _serverManager->CountActiveSessions();
  _timer->expires_at(_timer->expires_at() + boost::posix_time::seconds(updateTime));
  _timer->async_wait(boost::bind(&Server::CallBack_Debug_Print, this));
}

void		Server::Thread_TreatPacket()
{
  Packet	*packet;

  ///////////// THREAD SAFE ///////////////////////
  packet = _packetQueue->PopPacket();
  ////////////////////////////////////////////////
  
  _serverManager->Manage(packet);
  ////////////////////////// WAIT //////////////////
  usleep(treat_delay); // wait <treat_delay> to fake for delay introduced by treatment
  ////////////////////////// WAIT //////////////////
}


void		Server::Init(int argc, char *argv[])
{
  _argc = argc;
  _argv = argv;

  _debug_print_packet = 0;
  _debug_print_session = 0;
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
  _serverManager = new ServerManager(*_io_service, *_pool, *_socket);
  signal(SIGABRT, &sighandler);
  signal(SIGTERM, &sighandler);
  signal(SIGINT, &sighandler);
}

Server::~Server()
{
  _pool->clear();  // boost::threadpool probably calls it mut not documented
  delete _pool;
  delete _timer;
  delete _socket;
  delete _local_endpoint;
  delete _remote_endpoint;
  delete _io_service;
  delete _recv_buffer;
  delete _packetQueue;
  delete _serverManager;
  delete _config;  
}
