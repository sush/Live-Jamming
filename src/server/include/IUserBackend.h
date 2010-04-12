#ifndef __IUSERBACKEND_H__
#define __IUSERBACKEND_H__

#include <Singleton.h>

template <typename T>
class IUserBackend : public Singleton<T> {

 public :
  // All User informations methods
  virtual int Authentification() = 0;
  //  virtual RetrieveUserInfos() = 0;
};

#endif
