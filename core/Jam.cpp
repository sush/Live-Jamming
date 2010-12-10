#include <Jam.h>

Jam::Jam(Room *room)
{
  _room = room;
}

Jam::~Jam()
{}

Room *Jam::getRoom()
{
  return _room;
}

void		Jam::Start()
{
  _mutex.lock();
  _count = 0;
  _mutex.unlock();
}

void		Jam::Stop()
{
  _mutex.lock();
  _count = 0;
  _mutex.unlock();
}

void		Jam::Inc()
{
  _mutex.lock();
  ++_count;
  _mutex.unlock();
}

std::size_t	Jam::getCount()
{
  std::size_t	count;
  _mutex.lock();
  count = _count;
  _mutex.unlock();
  return count;
}
