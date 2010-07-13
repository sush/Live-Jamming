#include <ServerManager.h>
#include <Bind_recv.h>

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
  field_t			componentId = packet_v1->getComponentId(), requestId = packet_v1->getRequestId();
  session = _sessionManager->FindSession(packet_v1);

#ifdef _DEBUG
  std::cout << "<      RECV       > ";
  packet_v1->Print_v1();
#endif
  if (session)
    {
      session->setTimeOutTest();
      session->CancelTimeOutOccurred();

      if (IsRegisteredComponent(componentId))
	{
	  if (IsRegisteredRequest(componentId, requestId))
	    {
	      getBindRecv(componentId, requestId).Receive(packet_v1, session);
	      Request const & r = getRegisteredRequest(componentId, requestId);
	      if (r.IsResponseTo())
		session->CancelAutoRetry(componentId, r.getResponseTo());
	    }
	  else
	    std::cout << "UNREGISTERED REQUEST ID" << std::endl;
	}
      else
	std::cout << "UNREGISTERED COMPONENT ID" << std::endl;
    }
  else if (componentId == SESSION_COMPONENTID && requestId == SESSION_AUTHREQUEST)
    _sessionManager->Recv_AuthRequest(packet_v1, 0);
  else
    {
      //_sessionManager->PrintSession(packet);
      std::cout << "auth required" << std::endl;
      // send apropriate information
    }
}

void		ServerManager::Init_Components()
{
  _sessionManager = new Component_SessionManager(this);
  _channelManager = new Component_ChannelManager(this);
  _friendManager  = new Component_FriendManager(this);
  RegisterComponent(_sessionManager);
  RegisterComponent(_channelManager);
  RegisterComponent(_friendManager);
}

unsigned int	ServerManager::CountActiveSessions() const
{
  return _sessionManager->CountActiveSessions();
}

void		ServerManager::Disconnect(Session *session)
{
  _sessionManager->Disconnect(session);
  _channelManager->Disconnect(session);
}
