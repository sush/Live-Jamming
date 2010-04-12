#ifndef __SERVER_H__
#define __SERVER_H__

#include <iostream>
#include <Singleton.h>

namespace lj
{

  class Server : public Singleton<Server>
  {
    friend class Singleton<Server>;

  public:
    void	Run();
    void	Init(int, char *[]);
    
  private:

    int		_argc;
    char 	**_argv;
  };
}



#endif // ! __SERVER_H__ 
