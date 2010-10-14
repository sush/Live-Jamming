#include <Config.h>

Config::Config(int argc, char** const & argv) {
  BuildOption();
  // to change to be dynamic
  UpdateOptionFromConfig("config.yaml");
  UpdateOptionFromCommand(argc, argv);
}

Config::~Config() {}

int Config::OpenConfig(std::string const & filename) {
  _fd.open(filename.c_str());

  if (_fd)
    return 0;
  else
    return 1;
}

int Config::BuildConfig() {
  YAML::Parser parser(_fd);
  YAML::Node doc;

  try {
    parser.GetNextDocument(doc);
  } catch(YAML::ParserException& e) {
    std::cout << e.what() << "\n";
    return 1;
  }

  for(YAML::Iterator it = doc.begin(); it != doc.end(); ++it) {
    std::string key, value;
    it.first() >> key;
    it.second() >> value;
    _config.insert(m_config_pair(key, value));
  }
  return 0;
}
  
std::string const * Config::getValueFromConfig(std::string const & key) const {
  m_config_cit it;

  it = _config.find(key);
  if (it != _config.end()) {
    return &it->second;
  } 
  else
    return NULL;
}

std::vector<std::string> const * Config::getValueFromCommand(std::string const & key) const{
  if (_args.count(key)) {
    return &_args[key].as< std::vector<std::string> >();
   }
  return NULL;
}

void Config::BuildOption() {
  _options.insert(m_option_pair("ConfigFile", new Option("ConfigFile", "-f", "-file", "1", true, std::vector<std::string>(1, "config.yaml"))));
  _options.insert(m_option_pair("HostName", new Option("HostName", "-h", "-hostname", "1", true, std::vector<std::string>(1, "Live-Jamming"))));
  _options.insert(m_option_pair("Port", new Option("Port", "-p", "-port", "1", true, std::vector<std::string>(1, "5042"))));
  _options.insert(m_option_pair("BindAdress", new Option("BindAdress", "-b", "-bind", "1-", true, std::vector<std::string>(1, "0.0.0.0"))));
}

void Config::UpdateOptionFromConfig(std::string const & filename) {
  OpenConfig(filename);
  BuildConfig();

  m_option_cit it, end = _options.end();
  
  for (it = _options.begin(); it != end; ++it) {
    if (getValueFromConfig(it->first) != 0) {
      std::vector<std::string> configValue;
      configValue.push_back(*getValueFromConfig(it->first));
      Option *selectedOption = it->second;
      selectedOption->setValue(configValue);
    }
  }
}

void Config::UpdateOptionFromCommand(int argc, char** const & argv) {
  m_option_cit it, end = _options.end();
  
  Argument *argument = new Argument(argc, argv);
  _args = argument->getArgument();

  for (it = _options.begin(); it != end; ++it) {
    if (getValueFromCommand(it->first) != 0) {
      Option *selectedOption = it->second;
      selectedOption->setValue(*getValueFromCommand(it->first));
    }
  }
}

std::vector<std::string> const & Config::getValue(std::string const & key) {
  Option *selectedOption;

  selectedOption = _options[key];
  return selectedOption->getValue();
}
