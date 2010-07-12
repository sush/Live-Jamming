#include <Channel.h>

Channel::Channel(char const * name)
{
  _name = name;
  _connected = new m_session();
}

Channel::~Channel() {}

Channel::m_session	*Channel::getConnected()
{
  return _connected;
}

bool			Channel::addConnected(Session *session, field_t sessionId)
{
  if (_connected->find(sessionId) == _connected->end())
    {
      _channel_mutex.lock();
      _connected->insert(std::pair<field_t, Session *>(sessionId, session));
      _channel_mutex.unlock();
      return true;
    }
  return false;
}

bool			Channel::removeConnected(field_t sessionId)
{
  if (_connected->find(sessionId) != _connected->end())
    {
      _channel_mutex.lock();
      _connected->erase(sessionId);
      _channel_mutex.unlock();
      return true;
    }
  return false;
}

char const		*Channel::getName() const
{
  return _name;
}

void			Channel::setName(char const * name)
{
  _name = name;
}
