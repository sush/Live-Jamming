#include <ClientSession.h>

std::string	login = "o-conn_g";
std::string	pass = "o-conn_g";

char	server_ip[] =  "127.0.0.1";
int	server_port = 5042;

ClientSession::ClientSession(boost::asio::io_service & io_service, boost::threadpool::pool & pool,
			     boost::asio::ip::udp::socket & socket, boost::asio::ip::udp::endpoint & endpoint)
  : _io_service(io_service), _pool(pool), _socket(socket), _remote_endpoint(endpoint)
{
  Client_AuthRequest();
  _login = login;
  _pass = pass;
}

ClientSession::~ClientSession()
{

}

void		ClientSession::CallBack_handle_send()
{

}

void		ClientSession::Manage(Packet * packet)
{
  // send packet to appropriate zone
}

void		ClientSession::Client_AuthRequest()
{
  boost::array<char, PACKET_MAXSIZE> buffer;
  
  buffer[0] = 'l';
  buffer[1] = 'o';
  std::cout << "[0] = " << (unsigned short int)buffer[0]
	    << " [1] = " << (unsigned short int)buffer[1] << std::endl;
  // 2int sur 4 bit
  // [int sur 4 bits][int sur 4bits]
  //  7 puis 6
  //0111.0110 [8bits]
  // 7  . 6
  // 118 [8bits]
  // buffer[0] = 118

  _socket.async_send_to(boost::asio::buffer(buffer), _remote_endpoint,
			boost::bind(&ClientSession::CallBack_handle_send, this));
  // make buffer containing authRequestData
  // send 

}

void		ClientSession::Session_AuthResponse()
{
  // read buffer and get sessionId or look at what failed
}

void		ClientSession::Session_TimeOutTestRequest()
{
  // send timeOutTestResponse
}


void		ClientSession::Session_TimeOutTestResponse()
{
  
}

void		ClientSession::Session_Disconnect()
{
  // disconnect
}
