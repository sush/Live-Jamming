#ifndef __USERMODULE_MYSQL_H__
#define __USERMODULE_MYSQL_H_

#include <IUserBackend.h>
#include <IDatabase.h>
#include <mysql++/mysql++.h>

class UserModule_mysql : public IUserBackend<UserModule_mysql>, public IDatabase {

  friend class Singleton<UserModule_mysql>;

 public :
  virtual int Connection();
  virtual int Authentification();
  // RetrieveUserInfos();

 private :
  UserModule_mysql();
  virtual ~UserModule_mysql();
  // _dbLink;
};

#endif
