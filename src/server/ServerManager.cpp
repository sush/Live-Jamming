#include <ServerManager.h>

ServerManager::ServerManager(boost::asio::io_service & io_service, boost::threadpool::pool & pool, boost::asio::ip::udp::socket & socket)
  :Manager(io_service, pool, socket)
{
  // manual set but should be in options
  // remove when linked with option
  _retryDelay = 3;
  _timeOutTestDelay = 5;
  _timeOutOccurredDelay = 3;
  //

  Init_Components();
}

ServerManager::~ServerManager()
{}

void				ServerManager::Manage(Packet * packet)
{
  Session			*session;
  Packet_v1			*packet_v1;
  
  packet_v1 = static_cast<Packet_v1 *>(packet);
  session = _sessionManager->FindSession(packet_v1);

  std::cout << "==> ";
  packet_v1->Print_v1();
  if (session)
    {
      session->setTimeOutTest();
      session->CancelTimeOutOccurred();
      //_sessionManager->PrintSession(session);
      if (_bindingsRecv.find(packet_v1->getType()) != _bindingsRecv.end())
	_bindingsRecv.find(packet_v1->getType())->second->Receive(packet_v1, session);
      else
	std::cout << "UNKNOWN PACKET TYPE" << std::endl; // not implemented
    }
  else if (packet_v1->getType() == SESSION_AUTH_REQUEST)
    _sessionManager->DoAuth(packet_v1);
  else
    {
      //_sessionManager->PrintSession(packet);
      std::cout << "auth required" << std::endl;
      // send apropriate information
    }
}

void		ServerManager::Init_Components()
{
  _sessionManager = new Component_SessionManager(_bindingsRecv, this);
}

unsigned int	ServerManager::CountActiveSessions() const
{
  return _sessionManager->CountActiveSessions();
}

void		ServerManager::Disconnect(Session *session)
{
  _sessionManager->Disconnect(session);
}
