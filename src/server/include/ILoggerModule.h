#ifndef __ILOGGERMODULE_H__
#define __ILOGGERMODULE_H__

#include <Singleton.h>
#include <string>

template <typename T>
class ILoggerModule : public Singleton<T> {

 public :
  virtual void AddLine(int, std::string const &) const = 0;
};

#endif
