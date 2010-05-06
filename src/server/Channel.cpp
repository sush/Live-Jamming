#include <Channel.h>

Channel::Channel() {}

Channel::Channel(Session *session)
{
  addConnected(session);
}

Channel::~Channel() {}

std::vector<Session*> const & Channel::getConnected() const
{
  return _connected;
}

bool	Channel::addConnected(Session *session)
{
  if (!isConnected(session))
    {
      _channel_mutex.lock();
      _connected.push_back(session);
      _channel_mutex.unlock();
      return true;
    }
  return false;
}

bool	Channel::removeConnected(Session *session)
{
  for (unsigned int i = 0; i < _connected.size(); ++i)
    {
      Session selectedSession = (Session) _connected[i];
      if (selectedSession->getSessionId == session->getSessionId)
	{
	  if (isConnected(session))
	    {
	      _channel_mutex.lock();
	      _connected.erase(i);
	      _channel_mutex.unlock();
	      return true;
	    }
	}
    }
  return false;
}

bool	Channel::isConnected(Session *session)
{
  for (unsigned int i = 0; i < _connected.size(); ++i)
    {
      if (_connected[i] == session)
	return true;
    }
  return false;
}
