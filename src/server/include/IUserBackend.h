#ifndef __IUSERBACKEND_H__
#define __IUSERBACKEND_H__

#include <Singleton.h>

template <typename T>
class IUserBackend : public Singleton<T> {

  friend class Singleton<T>;

 public :
  virtual ~IUserBackend() {};
  virtual int Authentification() = 0;
  //  virtual RetrieveUserInfos() = 0;
};

#endif
