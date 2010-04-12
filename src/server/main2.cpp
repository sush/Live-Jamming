#include <iostream>
#include <UserModule_mysql.h>

int main(int argc, char *argv[]) {
  UserModule_mysql *userModule = UserModule_mysql::getInstance();
  std::cout << "Database Connection status : "<< userModule->Connection() << std::endl;
  return 0;
}
