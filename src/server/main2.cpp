 #include <iostream>
// #include <UserModule_mysql.h>

//#include "Config.h"
//#include "Argument.h"
//#include "Syslog.h"
// #include "Forge.h"

#include <Packet_v1.h>


int main(int argc, char *argv[]) {
  // authentification test
  //   UserModule_mysql *userModule = UserModule_mysql::getInstance();
  //   std::cout << "Database Connection status : "<< userModule->_status << std::endl;
  //   std::cout << "Login check status : " << userModule->Authentification("dude", "12345678") << std::endl;

  // Config & Arguments test
  //Config *conf = new Config("config.yaml", argc, argv);
  // Syslog *syslog = new Syslog();
  //   syslog->AddLine(1, "TEST LIVE-JAMMING!!!!!!!!!!!!");
  //  Argument *args = new Argument(argc, argv);
  Packet_v1* test = new Packet_v1(0);
  test->setProtoVersion(3);
  //  test->setType(42);
  //  std::cout << "proto = " << test->getProtoVersion() << " type = " << test->getType() << std::endl;
  std::cout << "proto = " << (int)(unsigned char)test->getProtoVersion() << std::endl;
    test->setType(42);
    std::cout << "type = " << (int)(unsigned char)test->getType() << std::endl;


  return 0;
}
