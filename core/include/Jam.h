#ifndef __JAM_H__
#define __JAM_H__

#include <iostream>
#include <Room.h>
#include <boost/thread.hpp>

class Jam
{
 public:

  Jam(Room *);
  virtual	~Jam();
  Room		*getRoom();
  void		Start();
  void		Stop();
  void		Inc();
  std::size_t	getCount();

 private:

  Room		*_room;
  std::size_t	_count;
  boost::mutex	_mutex;
};

#endif // ! __JAM_H__
