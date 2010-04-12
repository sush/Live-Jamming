#ifndef __IDATABASE_H__
#define __IDATABASE_H__

class IDatabase {

 private :
  // All inherent database methods
  virtual int Connection() = 0;
};

#endif
