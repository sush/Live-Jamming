#include <UserModule_mysql.h>

UserModule_mysql::UserModule_mysql() {}

UserModule_mysql::~UserModule_mysql() {}

int UserModule_mysql::Connection() {
  // define connection informations in an yaml file
  const char* db = "live-jamming_db", *server = "192.168.0.12", *user = "root", *pass = "MAgoun12$";
  mysqlpp::Connection _connection(false);
  
  if(_connection.connect(db, server, user, pass))
    return 0;
  else
    return 1;
}

int UserModule_mysql::Authentification() {
  return 0;
}
