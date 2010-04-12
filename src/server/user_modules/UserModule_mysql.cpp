#include <UserModule_mysql.h>

UserModule_mysql::UserModule_mysql() {
  Connection();
}

UserModule_mysql::~UserModule_mysql() {}

int UserModule_mysql::Connection() {
  // define connection informations in an yaml file
  const char* db = "live-jamming_db", *server = 0, *user = "root", *pass = "MAgoun12$";
  
  if(_dbLink.connect(db, server, user, pass)) {
    _status = 0;
    return 0;
  } else {
    _status = 1;
    return 1;
  }
}

int UserModule_mysql::Authentification(std::string const &login, std::string const &password) {
  std::string request = "SELECT * FROM users WHERE login = '"+login+"' AND password = SHA1('DYhG93b0qLive-JammingDIENOOBVoUubWwvniR2G0FgaC9mi"+password+"');";
  mysqlpp::Query query = _dbLink.query(request);

  if (mysqlpp::StoreQueryResult res = query.store()) {
    if (res.size() == 1)
      return 0;
  }
  return 1;
}
