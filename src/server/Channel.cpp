#include <Channel.h>

Channel::Channel() {}

Channel::Channel(Session *session, field_t sessionId)
{
  addConnected(session, sessionId);
}

Channel::~Channel() {}

std::map<field_t, Session*> const & Channel::getConnected() const
{
  return _connected;
}

bool	Channel::addConnected(Session *session, field_t sessionId)
{
  if (_connected[sessionId])
    {
      _channel_mutex.lock();
      _connected.insert(std::pair<field_t, Session *>(sessionId, session));
      _channel_mutex.unlock();
      return true;
    }
  return false;
}

bool	Channel::removeConnected(field_t sessionId)
{
  if (_connected[sessionId])
    {
      _channel_mutex.lock();
      _connected.erase(sessionId);
      _channel_mutex.unlock();
      return true;
    }
  return false;
}
