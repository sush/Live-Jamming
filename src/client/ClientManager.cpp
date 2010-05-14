#include <ClientManager.h>
#include <Component_Session.h>
#include <Session.h>
#include <Bind_recv.h>

ClientManager::ClientManager(boost::asio::io_service & io_service, boost::threadpool::pool & pool,
			     boost::asio::ip::udp::socket & socket, boost::asio::ip::udp::endpoint & remote_endpoint)
  :Manager::Manager(io_service, pool, socket), _remote_endpoint(remote_endpoint)
{
  Init_Components();
  // !!!!!!!!!!!!!!!!!!!!!
  // REMOVE THESE WHEN LINKED WITH OPTIONS
  // same as in server !!!!
  // !!!!!!!!!!!!!!!!!!!!!!!!
  _retryDelay = 1;
  _timeOutTestDelay = 10;
  _timeOutOccurredDelay = 5;
  _session->Connect("dude", "12345678");
}

ClientManager::~ClientManager()
{}

void				ClientManager::Manage(Packet * packet)
{
  // send packet to appropriate zone
  Packet_v1			*packet_v1;
  Session 			*session;
  static bool			exec_on_logged = 0;			

  packet_v1 = static_cast<Packet_v1 *>(packet);
  session = _session->getSession();
  
#ifdef _DEBUG
  std::cout << "<      RECV       > ";
  packet_v1->Print_v1();
#endif
  if (session)
    {
      session->setTimeOutTest();
      session->CancelTimeOutOccurred();
    }
  
  field_t	componentId = packet_v1->getComponentId(), requestId = packet_v1->getRequestId();
  if (IsRegisteredComponent(componentId))
    {
      if (IsBindRecv(componentId, requestId))
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

void			ClientManager::Init_Components()
{
  _session = new Component_Session(this);
  RegisterComponent(_session);
}
	   
void			ClientManager::Disconnect(Session *)
{
  _session->Disconnect();
}

boost::asio::ip::udp::endpoint        &ClientManager::getEndpoint()
{
  return _remote_endpoint;
}
