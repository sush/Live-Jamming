#include <iostream>
#include <Server.h>
#include <Protocol.h>
#include <Packet_v1_Session.h>
#include <Protocol_Session.h>

int		main(int argc, char *argv[])
{
  Server	*server = Server::getInstance();

  server->Init(argc, argv);
  server->Run();

  server->Delete();
  return 0;
}
