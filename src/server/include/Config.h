#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <yaml-cpp/yaml.h>
#include <Option.h>
#include <boost/program_options.hpp>
#include <Argument.h>

class Config {

 public :
  Config(int, char** const &);
  virtual ~Config();
  std::vector<std::string> const & getValue(std::string const &);
  void TraceOption();

 private :
  int OpenConfig(std::string const &);
  void BuildOption();
  int BuildConfig();
  void UpdateOptionFromConfig(std::string const &);
  void UpdateOptionFromCommand(int, char** const &);
  const std::string* getValueFromConfig(std::string const &) const;
  const std::vector<std::string>* getValueFromCommand(std::string const &) const;

  typedef std::multimap<std::string, std::string> m_config;
  m_config _config;
  std::map<std::string, Option*> _options;
  boost::program_options::variables_map _args;
  std::ifstream _fd;
};

#endif
