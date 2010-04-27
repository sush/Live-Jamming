#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
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

  typedef std::multimap<std::string, std::string> m_config;
  typedef m_config::const_iterator		  m_config_cit;
  typedef std::pair<std::string, std::string>	  m_config_pair;

  typedef std::map<std::string, Option*>	  m_option;
  typedef m_option::const_iterator		  m_option_cit;
  typedef std::pair<std::string, Option*>	  m_option_pair;

  int BuildConfig();
  int OpenConfig(std::string const &);
  void BuildOption();
  void UpdateOptionFromConfig(std::string const &);
  void UpdateOptionFromCommand(int, char** const &);
  std::string const *getValueFromConfig(std::string const &) const;
  std::vector<std::string> const *getValueFromCommand(std::string const &) const;

  m_config _config;
  m_option _options;
  boost::program_options::variables_map _args;
  std::ifstream _fd;
};

#endif
