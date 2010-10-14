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
