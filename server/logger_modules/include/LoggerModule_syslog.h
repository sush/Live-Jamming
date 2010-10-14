#ifndef __LOGGERMODULE_SYSLOG_H__
#define __LOGGERMODULE_SYSLOG_H__

#include <string>
#include <syslog.h>
#include <ILoggerModule.h>

//! SERVER: It is used to logg each events on the server.

class LoggerModule_syslog : public ILoggerModule<LoggerModule_syslog> 
{
  friend class Singleton<LoggerModule_syslog>;

 public :

  //! Default constructor.
  LoggerModule_syslog();
  //! Default destructor.
  virtual	~LoggerModule_syslog();

  //! Add line of events in syslog.
  void		AddLine(int, std::string const &) const;
};

#endif

