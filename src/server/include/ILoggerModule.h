#ifndef __ILOGGERMODULE_H__
#define __ILOGGERMODULE_H__

#include <Singleton.h>
#include <string>

//! SERVER: It is used to logg each events on the server.

template <typename T>
class ILoggerModule : public Singleton<T> {

 public :
  //! Default constructor.
  ILoggerModule();
  //! Default destructor.
  virtual	~ILoggerModule();
  //! Add line of events in syslog.
  /*!
\
   */
  virtual void	AddLine(int, std::string const &) const = 0;
};

#endif
