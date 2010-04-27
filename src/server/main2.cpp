 #include <iostream>
#include <UserModule_mysql.h>

//#include "Config.h"
//#include "Argument.h"
//#include "Syslog.h"
// #include "Forge.h"

int main(int argc, char *argv[]) {
  // authentification test
    UserModule_mysql *userModule = UserModule_mysql::getInstance();
    std::cout << "Login check status : " << userModule->Authentification("dude", "12345678") << std::endl;
    userModule->getProfil(16);

  // Config & Arguments test
  //Config *conf = new Config("config.yaml", argc, argv);
  //  Argument *args = new Argument(argc, argv);

  // Syslog test
  // Syslog *syslog = new Syslog();
  //   syslog->AddLine(1, "TEST LIVE-JAMMING!!!!!!!!!!!!");

  return 0;
}
