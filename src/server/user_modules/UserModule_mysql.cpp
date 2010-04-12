#include <UserModule_mysql.h>

UserModule_mysql::UserModule_mysql() {}

UserModule_mysql::~UserModule_mysql() {}

int UserModule_mysql::Connection() {
  // define connection informations in an yaml file
  const char* db = "live-jamming_db", *server = 0, *user = "root", *pass = "MAgoun12$";
  mysqlpp::Connection _connection = _connection.connect(db, server, user, pass);
  
  if(!_connection)
    return 1;
  else
    return 0;
}

int UserModule_mysql::Authentification() {
  return 0;
}
