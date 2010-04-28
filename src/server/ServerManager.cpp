#include <ServerManager.h>

ServerManager::ServerManager(boost::asio::io_service & io_service, boost::threadpool::pool & pool, boost::asio::ip::udp::socket & socket)
  :_io_service(io_service), _pool(pool), _socket(socket)
{
  Init_Components();
}

ServerManager::~ServerManager()
{}

boost::threadpool::pool		&ServerManager::getPool()
{
  return _pool;
}

boost::asio::io_service		&ServerManager::getIO()
{
  return _io_service;
}

void				ServerManager::Manage(Packet * packet)
{
  Session			*session;
  Packet_v1			*packet_v1;
  IComponent::PacketBind	*pb;
  
  packet_v1 = static_cast<Packet_v1 *>(packet);
  session = _sessionManager->FindSession(packet_v1);
  packet_v1->Print_v1();
  if (session)
    {
      session->setTimeOutTest();
      session->CancelTimeOutOccurred();
      //_sessionManager->PrintSession(session);
      if (_packetBindings.find(packet_v1->getType()) != _packetBindings.end())
	{
	  pb = &_packetBindings.find(packet_v1->getType())->second;
	  ((pb->instance)->*(pb->method))(packet_v1);
	}
    }
  else
    {
      //_sessionManager->PrintSession(packet);
      std::cout << " Unauthentificated -> Authentificating..." << std::endl;
      _sessionManager->DoAuth(packet_v1);
    }
}

void		ServerManager::CallBack_handle_send(Packet_v1 *packet_v1) const
{
  // segfaults
  //  delete packet_v1;
}

void		ServerManager::Send(Packet_v1 *packet_v1, Session * session) const
{
  packet_v1->setSessionId(session->getSessionId());
  _socket.async_send_to(boost::asio::buffer(packet_v1->getData()), session->getEndpoint(),
			boost::bind(&ServerManager::CallBack_handle_send, this, packet_v1));
}

void		ServerManager::Send(Packet_v1 *packet_v1, boost::asio::ip::udp::endpoint *endpoint) const
{
  _socket.async_send_to(boost::asio::buffer(packet_v1->getData()), *endpoint,
			boost::bind(&ServerManager::CallBack_handle_send, this, packet_v1));
}

void		ServerManager::Send(proto_v1_packet_type packetType, Session * session) const
{
  Packet_v1	*packet_v1 = new Packet_v1(&session->getEndpoint());

  packet_v1->setType(packetType);
  Send(packet_v1, session);
}

void		ServerManager::Init_Components()
{
  _sessionManager = new Component_SessionManager(_packetBindings, this);
}
