#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <IUserBackend.h>

class Database : public IUserBackend<Database> {

  friend class Singleton<Database>;

 public :
  virtual int Authentification();
  //  RetrieveUserInfos();

 private:
  Database();
  virtual ~Database();

  int Connection();
  //  Database _dbLink;

};

#endif
