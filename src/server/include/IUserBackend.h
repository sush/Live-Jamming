#ifndef __IUSERBACKEND_H__
#define __IUSERBACKEND_H__

#include <Singleton.h>

class IUserBackend : public Singleton<IUserBackend> {

  friend class Singleton<IUserBackend>;

 public :
  virtual ~IUserBackend() {};
  virtual int Authentification() = 0;
  //  virtual RetrieveUserInfos() = 0;
};

#endif
