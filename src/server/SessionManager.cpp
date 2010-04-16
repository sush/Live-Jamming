#include <SessionManager.h>

const int	session_timeout_test = 10;
const int	response_timeout = 2;

SessionManager::SessionManager(boost::asio::io_service const & io_service)
  :_io_service(io_service)
{

}

SessionManager::~SessionManager()
{}

void		SessionManager::Manage(Packet * packet)
{
  l_Session_cit	found = FindSession(packet);
  
  if (found != _sessionList.end())
    printf("found");
  else
    printf("not found");
}

SessionManager::l_Session_cit	SessionManager::FindSession(Packet const * packet) const
{
  l_Session_cit	it, end = _sessionList.end();

  for (it = _sessionList.begin(); it != end; ++it)
    //if (*it == *packet)
      return it;
  return end;
}

Session 	*SessionManager::DoAuth(Packet const * packet)
{
  Session	*new_session = new Session(_io_service, packet);

  _sessionList.push_back(new_session);
  return new_session;
}

void		SessionManager::Disconnect(Session const * session)
{
  std::cout << "disconnect" << std::endl;
  delete session;
}

void		SessionManager::TimeoutTest(Session const * session)
{


}
