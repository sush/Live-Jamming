#include <Database.h>

int main(int argc, char *argv[]) {
  Database *db = Database::getInstance();
  db->Authentification();
  return 0;
}
