#include <iostream>
#include <Client.h>

int		main(int argc, char *argv[])
{
  Client	*client = Client::getInstance();
  client->Init(argc, argv);
  client->Run();

  client->Delete();
  return 0;
}
