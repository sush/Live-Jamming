#include <ClientSession.h>

ClientSession::ClientSession(boost::asio::io_service & io_service, boost::threadpool::pool & pool,
			     boost::asio::ip::udp::socket & socket, boost::asio::ip::udp::endpoint & endpoint)
  : _io_service(io_service), _pool(pool), _socket(socket), _remote_endpoint(endpoint)
{
  Init_Components();
  _session->Connect("o-conn_g", "o-conn_g");
}

ClientSession::~ClientSession()
{}

void				ClientSession::Manage(Packet * packet)
{
  // send packet to appropriate zone
  Packet_v1			*packet_v1;
  IComponent::PacketBind	*pb;

  packet_v1 = static_cast<Packet_v1 *>(packet);
  std::cout << "type = " << packet_v1->getType() << std::endl;
  if (_packetBindings.find(packet_v1->getType()) != _packetBindings.end())
    {
      pb = &(_packetBindings.find(packet_v1->getType())->second);
      ((pb->instance)->*(pb->method))(packet_v1);
    }
  else
    std::cout << "UNKNOWN PACKET_TYPE (" << packet_v1->getType() << ")" << std::endl;

}
void			ClientSession::Init_Components()
{
  _session = new Component_Session(_packetBindings, _remote_endpoint, _socket);
}
