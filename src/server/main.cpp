#include <iostream>
#include <Server.h>

  int		main(int argc, char *argv[])
  {
    Server	*server = Server::getInstance();

    server->Init(argc, argv);
    server->Run();

    server->Delete();
    return 0;
  }
