#include <Server.h>

namespace lj
{
  void		Server::Run()
  {
    std::cout << "Server started..." << std::endl;
  }


  void		Server::Init(int argc, char *argv[])
  {
    _argc = argc;
    _argv = argv;

  }



}
