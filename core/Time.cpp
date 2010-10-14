#include <Time.h>

char		Time::_buffer[TIME_LENGTH];

char const *	Time::getTime()
{
  time_t		rawtime;
  tm *			ptm;

  time ( &rawtime );
  ptm = gmtime ( &rawtime );

  memset(Time::_buffer, 0, TIME_LENGTH);
  strftime(Time::_buffer, TIME_LENGTH, TIME_FORMAT, ptm);
  return Time::_buffer;
}

void			Time::Print()
{
  std::cout << "[" << Time::getTime() << "]";
}
