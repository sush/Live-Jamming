// #include <iostream>
// #include <UserModule_mysql.h>

#include "Config.h"

int main(int argc, char *argv[]) {
//   UserModule_mysql *userModule = UserModule_mysql::getInstance();
//   std::cout << "Database Connection status : "<< userModule->_status << std::endl;
//   std::cout << "Login check status : " << userModule->Authentification("dude", "12345678") << std::endl;

  Config *conf = new Config("config.yaml");
  conf->getConfig("port");

  return 0;
}
