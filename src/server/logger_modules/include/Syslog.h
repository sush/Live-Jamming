#ifndef __SYSLOG_H__
#define __SYSLOG_H__
#include <string>
#include <syslog.h>
#include <ILoggerModule.h>

class Syslog : public ILoggerModule<Syslog> {

  friend class Singleton<Syslog>;

 public :
  Syslog();
  virtual ~Syslog();
  void AddLine(int, std::string const &);
};

#endif // ! __SYSLOG_H__

