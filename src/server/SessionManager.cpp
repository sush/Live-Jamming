#include <SessionManager.h>

SessionManager::Packet_binding	SessionManager::Packet_type[] = 
  {
    {PROTO_AUTH_REQUEST, &SessionManager::AuthRequest},
    {PROTO_AUTH_RESPOND, &SessionManager::AuthRespond}
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
  l_Session_it	found = FindSession(packet);
  Session	*session;
  
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

SessionManager::l_Session_it	SessionManager::FindSession(Packet const * packet)
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

void		SessionManager::AuthRequest()
{

}

void		SessionManager::AuthRespond()
{

}


