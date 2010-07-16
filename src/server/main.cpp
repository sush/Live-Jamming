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

  Packet_v1_Session	*packet_v1 = new Packet_v1_Session(SESSION_AUTHREQUEST);
  packet_v1->setLogin("login");
  packet_v1->setPass("pass");
  //  packet_v1->Print();

  server->Delete();
  return 0;
}
