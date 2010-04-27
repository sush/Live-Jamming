#ifndef __USERMODULE_MYSQL_H__
#define __USERMODULE_MYSQL_H_
#include <iostream>
#include <sstream>
#include <map>
#include <IUserBackend.h>
#include <IDatabase.h>
#include <mysql++/mysql++.h>

class UserModule_mysql : public IUserBackend<UserModule_mysql>, public IDatabase {

  friend class Singleton<UserModule_mysql>;

 public :

  int Authentification(std::string const &, std::string const &);
  m_userinfo const *getProfil(int);
  m_userinfo const *getFriendList(int);

 private :
  UserModule_mysql();
  virtual ~UserModule_mysql();
  void Connection();

  mysqlpp::Connection _dbLink;
};

#endif
