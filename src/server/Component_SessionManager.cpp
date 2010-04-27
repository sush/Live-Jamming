#include <Component_SessionManager.h>

Component_SessionManager::Component_SessionManager(IComponent::m_packet_bindings &packetBindings,
						   boost::asio::io_service & io_service,
						   boost::asio::ip::udp::socket &socket,
						   boost::threadpool::pool & pool)
  :_packetBindings(packetBindings), _io_service(io_service), _socket(socket), _pool(pool)
{
  _sessionList = new l_Session;
  _rng.seed(std::clock());
  PacketBindings();
}

Component_SessionManager::~Component_SessionManager()
{}

unsigned int		Component_SessionManager::GenSessionId()
{
  unsigned int	sessionId;

  do {
    sessionId = _rng();
  } while (! IsUniqId(sessionId));
  return sessionId;
}

bool		Component_SessionManager::IsUniqId(unsigned int sessionId) const
{
  l_Session_it	it, end = _sessionList->end();

  for (it = _sessionList->begin(); it != end; ++it)
    if ((*it)->getSessionId() == sessionId)
      return false;
  return true;
}

void		Component_SessionManager::PrintSession(Session const * session) const
{
  std::cout << "[" << session->getIP() << ":" << session->getPort() << "]" <<
    "{" << session->getSessionId() << "}";

}

void		Component_SessionManager::PrintSession(Packet const * packet) const
{
  std::cout << "[" << packet->getEndpoint().address() << ":" << packet->getEndpoint().port() << "]" <<
    "{}";
}

Session		*Component_SessionManager::FindSession(Packet_v1 const * packet)
{
  l_Session_it	it, end = _sessionList->end();

  for (it = _sessionList->begin(); it != end; ++it)
    if (**it == *packet)
      return *it;
  return 0;
}

Component_SessionManager::l_Session_it	Component_SessionManager::FindSession_it(Session * session)
{
  l_Session_it	it, end = _sessionList->end();
  
  for (it = _sessionList->begin(); it != end; ++it)
    if (**it == *session)
      return it;
  return end;
}

Session 	*Component_SessionManager::DoAuth(Packet const * packet)
{
  // if packet is auth request type
  // extract auth information from
  
  Session	*new_session = new Session(this, _io_service, packet, GenSessionId());

  _sessionList->push_back(new_session);
  return new_session;
}

void		Component_SessionManager::Disconnect(Session * session)
{
  l_Session_it	it = FindSession_it(session);

  PrintSession(*it);
  std::cout << " Disconnected" << std::endl;
  _sessionList->erase(it);
}

void		Component_SessionManager::Send_TimeOutTest(Session * session)
{
  l_Session_it	it = FindSession_it(session);

  PrintSession(*it);
  std::cout << " Testing Session" << std::endl;
  session->CancelTimeOutTest();
  session->setTimeOutOccurred();
}

void		Component_SessionManager::CallBack_TimeOutTest(Session * session, boost::system::error_code const & error_code)
{
  if (error_code != boost::asio::error::operation_aborted)
    _pool.schedule(boost::bind(&Component_SessionManager::Send_TimeOutTest, this, session));
}

void		Component_SessionManager::CallBack_TimeOutOccurred(Session * session, boost::system::error_code const & error_code)
{
  if (error_code != boost::asio::error::operation_aborted)
    _pool.schedule(boost::bind(&Component_SessionManager::Disconnect, this, session));
}

void				Component_SessionManager::Recv_AuthRequest(Packet_v1 *packet_v1)
{
  Packet_v1_Session_AuthRequest	*packet_authRequest =
    static_cast<Packet_v1_Session_AuthRequest *>(packet_v1);

  std::cout << "packet_auth_request received" << std::endl;
}

void		Component_SessionManager::Send_AuthResponse()
{
  
}

void		Component_SessionManager::Recv_KeepAlive(Packet_v1 *)
{
  std::cout << "packet_keep_alive received" << std::endl;
}

void		Component_SessionManager::Recv_TimeOutTest(Packet_v1 *)
{
  std::cout << "packet_timeout received" << std::endl;
}

void		Component_SessionManager::Recv_Disconnect(Packet_v1 * packet_v1)
{
  //  l_Session_it	it = FindSession(packet_v1);

  //  PrintSession(*it);
  std::cout << " recv_Disconnected" << std::endl;
  //  _sessionList->erase(it);
}

void		Component_SessionManager::PacketBindings()
{
  _packetBindings[SESSION_AUTH_REQUEST] =
    {this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_AuthRequest)};
  _packetBindings[SESSION_KEEPALIVE] =
    {this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_KeepAlive)};
  _packetBindings[SESSION_DISCONNECT] =
    {this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_Disconnect)};
  _packetBindings[SESSION_TIMEOUT] =
    {this, static_cast<IComponent::pMethod>(&Component_SessionManager::Recv_TimeOutTest)};
}
