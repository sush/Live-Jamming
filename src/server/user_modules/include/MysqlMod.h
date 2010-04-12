#ifndef __MYSQLMOD_H__
#define __MYSQLMOD_H_

#include <IUserBackend.h>
#include <IDatabase.h>

class MysqlMod : public IUserBackend<MysqlMod>, public IDatabase {

  friend class Singleton<MysqlMod>;

 public :
  virtual int Authentification();
  // RetrieveUserInfos();

 private :
  MysqlMod();
  virtual ~MysqlMod();
  virtual int Connection();
  // _dbLink;
};

#endif
