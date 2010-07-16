#ifndef __JAM_H__
#define __JAM_H__

#include <Room.h>

class Jam
{
 public:

  Jam(Room *);
  virtual	~Jam();
  Room		*getRoom();

 private:

  Room		*_room;
};

#endif // ! __JAM_H__
