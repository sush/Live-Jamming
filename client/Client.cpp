#include <Client.h>
#include <stdexcept>
#include <Packet_v1.h>
#include <sstream>
#include <string>
#include <LJ_Time.h>

char const	*connect_address = "127.0.0.1";

int		Client::_connect_port	= 5042;
int		Client::_port	= _connect_port + 1;
int		Client::_poolSize = 2;
const int	updateTime = 1;

void		Client::Run()
{
  std::cerr << "* ";
  Time::Print();
  std::cerr << "Client started..." << std::endl;
 
  start_receive();
  _io_service->reset();
  _io_service->run();
}

void Client::start_receive()
{
  _recv_buffer = new Packet::buffer_t;
  _socket->async_receive_from(boost::asio::buffer(*_recv_buffer), *_remote_endpoint,
			      boost::bind(&Client::CallBack_handle_receive, this,
					  boost::asio::placeholders::error,
					  boost::asio::placeholders::bytes_transferred));
}

void	Client::CallBack_handle_receive(boost::system::error_code const & error, std::size_t recv_count)
{
  if (!error || error == boost::asio::error::message_size)
    {

      //      std::cout << "HANDLE RECEIVE....................." << (int)_recv_buffer << std::endl;
      ////////// THREAD SAFE//////////////////////
      // !!! to implement !!!
      // this lock should have a very high priority for locking
      // the main receiver thread shouldn t be waiting for all thread workers finishing to treat
      // packets
      ///////////////////////////////////////////////////////
      // MOVED THE LOCK INSIDE CLASS: ADD INT PARAMETER FOR LOCKING PRIORITY

      try {
	//	std::cout << ">>before cond_new_packet<<" << std::endl;
	Packet * p = reinterpret_cast<Packet *>(_clientManager->Cond_new_Packet(*_remote_endpoint, *_recv_buffer, recv_count));
	//      std::cout << ">>after cond_new_packet<< (" <<((Packet_v1 *)p)->getComponentId()<< ", " << ((Packet_v1 *)p)->getRequestId() << ")" << std::endl;
	_packetQueue->PushPacket(p);
	_pool->schedule(boost::bind(&Client::Thread_TreatPacket, this));
      }
      catch (std::runtime_error &e)
	{
	  std::cout << e.what() << ":" << Packet_v1::peekComponentId(*_recv_buffer) << std::endl;
	  delete _recv_buffer;
	}
      ////////////////////////////////////////////

      start_receive();
    }
}

void		Client::CallBack_Debug_Print()
{
#ifdef _DEBUG
  if (_debug_print_packet != _packetQueue->getPacketCount())
    {
      std::cerr << Time::getTime() << " [PaquetQueue] packet_no[" << _packetQueue->getPacketCount() << "] MaxSize = " << _packetQueue->getMaxSize() << ", Size = " << _packetQueue->getSize() << std::endl;
    }
  _debug_print_packet = _packetQueue->getPacketCount();
#endif
  _timer->expires_at(_timer->expires_at() + boost::posix_time::seconds(updateTime));
  _timer->async_wait(boost::bind(&Client::CallBack_Debug_Print, this));
}

void		Client::Thread_TreatPacket()
{
  Packet	*packet;

  ///////////// THREAD SAFE ///////////////////////
  packet = _packetQueue->PopPacket();
  ////////////////////////////////////////////////

  //        packet->Print();
  _clientManager->Manage(packet);
  delete packet;
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
	//delete _local_endpoint;
	_local_endpoint = 0;
      }
  }
  while (!_local_endpoint);
}

void		Client::Connect(std::string const & login, std::string const & password, std::string const & server, int port)
{
  // string to int
  connect_address = server.c_str();
  _connect_port = port;
  _remote_endpoint->address(boost::asio::ip::address::from_string(connect_address));
  _remote_endpoint->port(port);
  static int aaa = 0;
  if (aaa == 0)
    boost::thread		t(boost::bind(&Client::Run, this));
  _clientManager->Connect(login, password);

  ++aaa;
}

void		Client::Disconnect()
{
  _clientManager->Disconnect(0);
#ifdef _DEBUG
  std::cerr << "[PACKET ALLOCATION SUMMARY] alloc = " << alloc_count << ", free = " << free_count << ", diff = " << alloc_count - free_count << std::endl;
#endif
}

void		Client::Init(int argc, char *argv[])
{
  _argc = argc;
  _argv = argv;
  _debug_print_packet = 0;
  _io_service = new boost::asio::io_service;
  _remote_endpoint = new boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(connect_address), Client::_connect_port);
  _socket = new boost::asio::ip::udp::socket (*_io_service);
  _socket->open(boost::asio::ip::udp::v4());
  BindToLocalPort();
  _packetQueue = new PacketQueue;

  _timer = new boost::asio::deadline_timer(*_io_service, boost::posix_time::seconds(updateTime));
  _timer->async_wait(boost::bind(&Client::CallBack_Debug_Print, this));
  _pool = new boost::threadpool::pool(_poolSize);
  ///////////  ///////////  ///////////  ///////////  ///////////  ///////////  ///////////
  //  _clientManager = new ClientManager(*_io_service, *_pool, *_socket, *_remote_endpoint);
  MainWindow::gui_init(argc, argv);
  Proxy proxy(this, *_io_service, *_pool, *_socket, *_remote_endpoint);
  MainWindow guiInstance(&proxy);
  _clientManager = &proxy;
  MainWindow::run();
}
