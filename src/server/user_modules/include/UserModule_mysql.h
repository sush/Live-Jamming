#ifndef __USERMODULE_MYSQL_H__
#define __USERMODULE_MYSQL_H_

#include <IUserBackend.h>
#include <IDatabase.h>
#include <mysql++/mysql++.h>

class UserModule_mysql : public IUserBackend<UserModule_mysql>, public IDatabase {

  friend class Singleton<UserModule_mysql>;

 public :
  virtual int Authentification(std::string const &, std::string const &);
  int _status; // to remove here for connectivity test
  // RetrieveUserInfos();

 private :
  UserModule_mysql();
  virtual ~UserModule_mysql();
  virtual int Connection();
  mysqlpp::Connection _dbLink;
};

#endif
