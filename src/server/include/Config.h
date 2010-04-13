#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <yaml-cpp/yaml.h>

class Config {

 public :
  Config(std::string const &);
  virtual ~Config();
  std::string const & getConfig(std::string const &);

 private :
  int OpenConfig(std::string const &);
  int BuildConfig();
  std::map <std::string, std::string> _config;
  std::ifstream _fd;
};

#endif
