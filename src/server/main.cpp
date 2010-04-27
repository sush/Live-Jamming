#include <iostream>
#include <Server.h>
#include <Protocol.h>

int		main(int argc, char *argv[])
{
  Server	*server = Server::getInstance();

  std::cout << "PROTOV1_START_OF_DATA = " << PROTOV1_START_OF_DATA << std::endl;

  server->Init(argc, argv);
  server->Run();

  server->Delete();
  return 0;
}
