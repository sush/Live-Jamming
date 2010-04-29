#include <ClientManager.h>

ClientManager::ClientManager(boost::asio::io_service & io_service, boost::threadpool::pool & pool,
			     boost::asio::ip::udp::socket & socket, boost::asio::ip::udp::endpoint & endpoint)
  :_io_service(io_service), _pool(pool), _socket(socket), _remote_endpoint(endpoint)
{
  Init_Components();
  _session->Connect("o-conn_g", "o-conn_g");
}

ClientManager::~ClientManager()
{}

void				ClientManager::Manage(Packet * packet)
{
  // send packet to appropriate zone
  Packet_v1			*packet_v1;
  IComponent::PacketBind	*pb;

  packet_v1 = static_cast<Packet_v1 *>(packet);
  packet_v1->Print_v1();
  if (_packetBindings.find(packet_v1->getType()) != _packetBindings.end())
    {
      pb = &(_packetBindings.find(packet_v1->getType())->second);
      ((pb->instance)->*(pb->method))(packet_v1);
    }
  else
    std::cout << "UNKNOWN PACKET_TYPE (" << packet_v1->getType() << ")" << std::endl;

}

void			ClientManager::Init_Components()
{
  _session = new Component_Session(_packetBindings, this);
}

boost::asio::ip::udp::endpoint &	ClientManager::getEndpoint()
{
  return _remote_endpoint;
}

boost::asio::io_service		&ClientManager::getIO()
{
   return _io_service;
}


void		ClientManager::CallBack_handle_send(Packet_v1 *packet_v1) const
{
  // segfaults
  //  delete packet_v1;
}

void		ClientManager::Send(Packet_v1 *packet_v1) const
{
  packet_v1->setSessionId(_session->getSessionId());
  _socket.async_send_to(boost::asio::buffer(packet_v1->getData()), _remote_endpoint,
			boost::bind(&ClientManager::CallBack_handle_send, this, packet_v1));
}

void		ClientManager::Send(proto_v1_packet_type packetType) const
{
  Packet_v1	*packet_v1 = new Packet_v1(&_remote_endpoint);

  packet_v1->setType(packetType);
  Send(packet_v1);
}
