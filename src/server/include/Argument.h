#ifndef __ARGUMENT_H__
#define __ARGUMENT_H__

#include <iostream>
#include <string>
#include <map>
#include <boost/program_options.hpp>
#include <iostream>

class Argument {

 public :
  Argument(int, char** const &);
  virtual ~Argument();
  boost::program_options::variables_map getArgument();

 private :
  int BuildCommandLine(int argc, char** const & argv);
  std::map<std::string, std::string> & ParseArguments(int, char** const &);
  boost::program_options::variables_map _args;
};

#endif
