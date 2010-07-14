#include <Room.h>

Room::Room(char const * name)
{
  _name = name;
  _connected = new m_session();
}

Room::~Room() {}

Room::m_session		*Room::getConnected()
{
  return _connected;
}

bool                    Room::addConnected(Session *session, field_t sessionId)
{
  if (_connected->find(sessionId) == _connected->end())
    {
      _room_mutex.lock();
      _connected->insert(std::pair<field_t, Session *>(sessionId, session));
      _room_mutex.unlock();
      return true;
    }
  return false;
}

bool                    Room::removeConnected(field_t sessionId)
{
  if (_connected->find(sessionId) != _connected->end())
    {
      _room_mutex.lock();
      _connected->erase(sessionId);
      _room_mutex.unlock();
      return true;
    }
  return false;
}

char const              *Room::getName() const
{
  return _name;
}

void                    Room::setName(char const * name)
{
  _name = name;
}
