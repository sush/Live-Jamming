#include <iostream>
#include <UserModule_mysql.h>

int main(int argc, char *argv[]) {
  UserModule_mysql *userModule = UserModule_mysql::getInstance();
  std::cout << "Database Connection status : "<< userModule->_status << std::endl;
  std::cout << "Login check status : " << userModule->Authentification("dude", "12345678") << std::endl;
  return 0;
}
