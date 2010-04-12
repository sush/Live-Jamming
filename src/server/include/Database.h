#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <IUserBackend.h>

class Database : public IUserBackend {

 public :
  virtual int Authentification();
  //  RetrieveUserInfos();

 private :
  Database();
  virtual ~Database();
  int Connection();
  //  Database _dbLink;

};

#endif
