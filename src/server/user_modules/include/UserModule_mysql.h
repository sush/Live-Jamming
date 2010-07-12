#ifndef __USERMODULE_MYSQL_H__
#define __USERMODULE_MYSQL_H_
#include <iostream>
#include <sstream>
#include <map>
#include <IUserBackend.h>
#include <IDatabase.h>
#include <mysql++/mysql++.h>

//! SERVER: It is use to manage all user module methods with Mysql.

class UserModule_mysql : public IUserBackend<UserModule_mysql>, public IDatabase
{
  friend class Singleton<UserModule_mysql>;

 public :

  IUserBackend<UserModule_mysql>::m_userinfo const *	Authentification(std::string const &, std::string const &);
  m_userinfo const					*getProfil(int);
  std::vector<std::string> const &			getFriendList(std::string const &);

 private :
  UserModule_mysql();
  virtual		 ~UserModule_mysql();
  void			Connection();

  mysqlpp::Connection	_dbLink;
};

#endif
