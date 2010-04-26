#include <ServerManager.h>

ServerManager::ServerManager(boost::asio::io_service & io_service, boost::threadpool::pool & pool)
  :_io_service(io_service), _pool(pool)
{
  _socket = new boost::asio::ip::udp::socket(_io_service);
  Init_Components();
}

ServerManager::~ServerManager()
{}

void				ServerManager::Manage(Packet * packet)
{
  Session			*session;
  Packet_v1			*packet_v1;
  IComponent::PacketBind	*pb;

  packet_v1 = static_cast<Packet_v1 *>(packet);
  std::cout << "[proto_version] " << packet_v1->getProtoVersion() << " [type] " << packet_v1->getType() << std::endl;
  session = _sessionManager->FindSession(packet_v1);
  if (session)
    {
      session->setTimeOutTest();
      session->CancelTimeOutOccurred();
      _sessionManager->PrintSession(session);
      if (_packetBindings.find(packet_v1->getType()) != _packetBindings.end())
	{
	  pb = &_packetBindings.find(packet_v1->getType())->second;
	  ((pb->instance)->*(pb->method))(packet_v1);
	}
      else
	std::cout << "UNKNOWN PACKET_TYPE (" << packet_v1->getType() << ")" << std::endl;
    }
  else
    {
      _sessionManager->PrintSession(packet);
      std::cout << " Unauthentificated -> Authentificating..." << std::endl;
      _sessionManager->DoAuth(packet);
    }
}

void		ServerManager::Init_Components()
{
  _sessionManager = new Component_SessionManager(_packetBindings, _io_service, *_socket, _pool);
}
