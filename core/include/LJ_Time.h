#ifndef __LJ_TIME_H__
#define __LJ_TIME_H__

#include <ctime>
#include <time.h>
#include <iostream>
#include <string.h>

#define TIME_FORMAT	"%a %d %b %Y %X"
#define TIME_LENGTH	32

class Time
{
public:  

  static char const *	getTime();
  static void		Print();

private:
  Time();
  ~Time();
  
  static char		_buffer[TIME_LENGTH];
};

#endif // ! __LJ_TIME_H__
