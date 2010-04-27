#ifndef __LOGGERMODULE_SYSLOG_H__
#define __LOGGERMODULE_SYSLOG_H__
#include <string>
#include <syslog.h>
#include <ILoggerModule.h>

class LoggerModule_syslog : public ILoggerModule<Syslog> {

  friend class Singleton<LoggerModule_syslog>;

 public :
  LoggerModule_syslog();
  virtual ~LoggerModule_syslog();
  void AddLine(int, std::string const &);
};

#endif

