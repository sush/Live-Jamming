#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <fstream>
#include <map>
#include <yaml-cpp/yaml.h>
#include <Option.h>
#include <boost/program_options.hpp>
#include <Argument.h>

//! SERVER: Load server configuration from file / command line.

class Config 
{
 public :
  
  //! Constructor.
  /*!
    \param 1 command line argc
    \param 2 command line argv
  */
  Config(int, char** const &);
  //! Default destructor.
  virtual ~Config();

  //! Get value of a specified option.
  /*! \param 1 index of value wanted. */
  std::vector<std::string> const &	getValue(std::string const &);
  void					TraceOption();

 private :

  typedef std::multimap<std::string, std::string>	m_config;
  typedef m_config::const_iterator			m_config_cit;
  typedef std::pair<std::string, std::string>		m_config_pair;

  typedef std::map<std::string, Option*>		m_option;
  typedef m_option::const_iterator			m_option_cit;
  typedef std::pair<std::string, Option*>		m_option_pair;

  //! Build config from file.
  /*! \return 0 if ok or 1 if not. */
  int					BuildConfig();
  //! Open config file.
  /*! \param 1 config file name. */
  /*! \return 0 if ok or 1 if not. */
  int					OpenConfig(std::string const &);
  //! Build options.
  void					BuildOption();
  //! Update option with config file values.
  /*! \param 1 config file name. */
  void					UpdateOptionFromConfig(std::string const &);
  //! Update option with command line.
  /*! \params command line parameters. */
  void					UpdateOptionFromCommand(int, char** const &);

  //! Get value of an option from config
  /*! \param 1 index of value wanted. */
  /*! \return const ref string value of option. */
  std::string const			*getValueFromConfig(std::string const &) const;
  //! Get value of an option from command
  /*! \param 1 index of value wanted. */
  /*! \return const ref string value of option. */
  std::vector<std::string> const	*getValueFromCommand(std::string const &) const;

  m_config				_config;
  m_option				_options;
  boost::program_options::variables_map _args;
  std::ifstream				_fd;
};

#endif
