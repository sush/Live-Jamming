#include <UserModule_mysql.h>

UserModule_mysql::UserModule_mysql() {
  Connection();
}

UserModule_mysql::~UserModule_mysql() {}

void UserModule_mysql::Connection() {
  const char* db = "live-jamming_db", *server = "192.168.0.12", *user = "root", *pass = "MAgoun12$";
  
  _dbLink.connect(db, server, user, pass);
}

int UserModule_mysql::Authentification(std::string const &login, std::string const &password) {
  std::string request = "SELECT * FROM users WHERE login = '"
    +login+"' AND password = SHA1('DYhG93b0qLive-JammingDIENOOBVoUubWwvniR2G0FgaC9mi"+password+"');";
  
  mysqlpp::Query query = _dbLink.query(request);
  
  if (mysqlpp::StoreQueryResult res = query.store()) {
    if (res.size() == 1)
      return 0;
  }

  return 1;
//   mysqlpp::Query query = _dbLink.query(request);
//   mysqlpp::StoreQueryResult res = query.store();
//   mysqlpp::StoreQueryResult::const_iterator it, end = res.end();

//   if (res.size() == 1) {
//     for (it = res.begin(); it != end; ++it) {
//       mysqlpp::Row row = (*it);
//       //      return row['id'];
//     }
//   }
//   return 1;

}

UserModule_mysql::m_userinfo const * UserModule_mysql::getProfil(int sessionId) {
  m_userinfo *profil = new m_userinfo;

  std::ostringstream oss;
  oss << "SELECT * FROM users WHERE id = " << sessionId << ";";
  std::string request = oss.str();

  mysqlpp::Query query = _dbLink.query(request);
  mysqlpp::StoreQueryResult res = query.store();
  mysqlpp::StoreQueryResult::const_iterator it, end = res.end();

  for (it = res.begin(); it != end; ++it) {
    mysqlpp::Row row = (*it);
    profil->insert(m_userinfo_pair("id", (std::string)row["id"]));
    std::cout << "RES: "<< row["id"] << std::endl;
  }

  return profil;
}

UserModule_mysql::m_userinfo const * UserModule_mysql::getFriendList(int sessionId) {
  m_userinfo *friendList = new m_userinfo;
  friendList = 0;
  sessionId = 0;

  return friendList;
}
