#include <SessionManager.h>

SessionManager::Packet_binding	SessionManager::Packet_type[] = 
  {
    {SESSION_AUTH_REQUEST,	&SessionManager::Packet_AuthRequest},
    {SESSION_KEEPALIVE,		&SessionManager::Packet_KeepAlive},
    {SESSION_DISCONNECT,	&SessionManager::Packet_Disconnect},
    {SESSION_TIMEOUT,		&SessionManager::Packet_TimeOut}
  };

SessionManager::SessionManager(boost::asio::io_service & io_service, boost::threadpool::pool & pool)
  :_io_service(io_service), _pool(pool)
{
  _sessionList = new l_Session;
  _rng.seed(std::clock());
}

SessionManager::~SessionManager()
{}

unsigned int		SessionManager::GenSessionId()
{
  unsigned int	sessionId;

  do {
    sessionId = _rng();
  } while (! IsUniqId(sessionId));
  return sessionId;
}

bool		SessionManager::IsUniqId(unsigned int sessionId) const
{
  l_Session_it	it, end = _sessionList->end();

  for (it = _sessionList->begin(); it != end; ++it)
    if ((*it)->getSessionId() == sessionId)
      return false;
  return true;
}

void		SessionManager::Manage(Packet * packet)
{
  l_Session_it	found;
  Session	*session;
  Packet_v1	*packet_v1;

  packet_v1 = dynamic_cast<Packet_v1 *>(packet);
  found = FindSession(packet_v1);
  FindSession(packet_v1);
  if (found != _sessionList->end())
    {
      (*found)->setTimeOutTest();
      (*found)->CancelTimeOutOccurred();
      PrintSession(*found);
      std::cout << " Authentificated." << std::endl;
    }
  else
    {
      PrintSession(packet);
      std::cout << " Unauthentificated -> Authentificating..." << std::endl;
      session = DoAuth(packet);
    }
}

void		SessionManager::PrintSession(Session const * session) const
{
  std::cout << "[" << session->getIP() << ":" << session->getPort() << "]" <<
    "{" << session->getSessionId() << "}";

}

void		SessionManager::PrintSession(Packet const * packet) const
{
      std::cout << "[" << packet->getEndpoint().address() << ":" << packet->getEndpoint().port() << "]" <<
	"{}";
}

SessionManager::l_Session_it	SessionManager::FindSession(Packet_v1 const * packet)
{
  l_Session_it	it, end = _sessionList->end();

  for (it = _sessionList->begin(); it != end; ++it)
    if (**it == *packet)
      return it;
  return end;
}

SessionManager::l_Session_it	SessionManager::FindSession(Session * session)
{
  l_Session_it	it, end = _sessionList->end();

  for (it = _sessionList->begin(); it != end; ++it)
    if (**it == *session)
      return it;
  return end;
}

Session 	*SessionManager::DoAuth(Packet const * packet)
{
  // if packet is auth request type
  // extract auth information from

  Session	*new_session = new Session(this, _io_service, packet, GenSessionId());

  _sessionList->push_back(new_session);
  return new_session;
}

void		SessionManager::Disconnect(Session * session)
{
  l_Session_it	it = FindSession(session);

  PrintSession(*it);
  std::cout << " Disconnected" << std::endl;
  _sessionList->erase(it);
}

void		SessionManager::TimeOutTest(Session * session)
{
  l_Session_it	it = FindSession(session);

  PrintSession(*it);
  std::cout << " Testing Session" << std::endl;
  session->CancelTimeOutTest();
  session->setTimeOutOccurred();
}

void		SessionManager::CallBack_TimeOutTest(Session * session, boost::system::error_code const & error_code)
{
  if (error_code != boost::asio::error::operation_aborted)
    _pool.schedule(boost::bind(&SessionManager::TimeOutTest, this, session));
}

void		SessionManager::CallBack_TimeOutOccurred(Session * session, boost::system::error_code const & error_code)
{
  if (error_code != boost::asio::error::operation_aborted)
    _pool.schedule(boost::bind(&SessionManager::Disconnect, this, session));
}

void		SessionManager::Packet_AuthRequest(Packet_v1 *)
{

}

void		SessionManager::AuthRespond()
{

}

void		SessionManager::Packet_KeepAlive(Packet_v1 *)
{

}

void		SessionManager::Packet_TimeOut(Packet_v1 *)
{

}

void		SessionManager::Packet_Disconnect(Packet_v1 * packet_v1)
{
  l_Session_it	it = FindSession(packet_v1);

  PrintSession(*it);
  std::cout << " Disconnected" << std::endl;
  _sessionList->erase(it);

}
