#ifndef __ILOGGERMODULE_H__
#define __ILOGGERMODULE_H__

#include <Singleton.h>
#include <string>

//! SERVER: Interface defines mandatory methods to log events on server.

template <typename T>
class ILoggerModule : public Singleton<T> {

 public :

  //! Add line of events in syslog.
  virtual void	AddLine(int, std::string const &) const = 0;
};

#endif
