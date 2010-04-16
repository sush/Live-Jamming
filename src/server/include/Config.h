#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <yaml-cpp/yaml.h>
#include "Option.h"
#include <boost/program_options.hpp>
#include "Argument.h"

class Config {

 public :
  Config(std::string const &, int, char** const &);
  virtual ~Config();
  Option* getSelectedOption(std::string const &);
  void TraceOption();

 private :
  int OpenConfig(std::string const &);
  void BuildOption();
  int BuildConfig();
  void UpdateOptionFromConfig(std::string const &);
  void UpdateOptionFromCommand(int, char** const &);
  std::string* getValueFromConfig(std::string const &);
  std::vector<std::string>* getValueFromCommand(std::string const &);
  std::multimap<std::string, std::string> _config;
  std::map<std::string, Option*> _options;
  boost::program_options::variables_map _args;
  std::ifstream _fd;
};

#endif
