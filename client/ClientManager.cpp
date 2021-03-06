#include <ClientManager.h>
#include <Component_Session.h>
#include <Component_Channel.h>
#include <Component_Friend.h>
#include <Component_Room.h>
#include <Component_Jam.h>
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
  _timeOutTestDelay = 40;
  _timeOutOccurredDelay = 5;
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
  std::cout << std::endl;
  std::cout << "<      RECV       > ";
  packet_v1->Print("", this);
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
  _channel = new Component_Channel(this);
  _friend  = new Component_Friend(this);
  _room  = new Component_Room(this);
  _jam  = new Component_Jam(this);
  RegisterComponent(_session);
  RegisterComponent(_channel);
  RegisterComponent(_friend);
  RegisterComponent(_room);
  RegisterComponent(_jam);
}

void			ClientManager::Connect(std::string const &login, std::string const &password)
{
  _session->Connect(login, password);
}

void			ClientManager::Disconnect(Session *)
{
  Session		* session = _session->getSession();

  _session->Disconnect(session);
  _channel->Disconnect(session);
  _room->Disconnect(session);
  _friend->Disconnect(session);
  static_cast<Proxy*>(this)->disconnect(); // session_timeout, connection_timeout
  std::cout << "session = " << session << std::endl;
  std::cout << "session = " << session << std::endl;
  session->DeAuthentificated();
  //  _io_service.stop();
}

boost::asio::ip::udp::endpoint        &ClientManager::getEndpoint()
{
  return _remote_endpoint;
}

Component_Jam			      *ClientManager::getComponentJam()
{
  return _jam;
}

ClientManager::m_user &			ClientManager::getUserMap()
{
  return _userMap;
}

ClientManager::m_avatar &		ClientManager::getAvatarMap()
{
  return _avatarMap;
}

