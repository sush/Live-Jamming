#include <iostream>
#include <Server.h>

  int		main(int argc, char *argv[])
  {
    lj::Server	*server = lj::Server::getInstance();

    server->Init(argc, argv);
    server->Run();

    server->Delete();
    return 0;
  }
