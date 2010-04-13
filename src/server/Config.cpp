#include "Config.h"

Config::Config(std::string const & filename) {
  OpenConfig(filename);
  BuildConfig();
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

  for(YAML::Iterator it=doc.begin();it!=doc.end();++it) {
    std::string key, value;
    it.first() >> key;
    it.second() >> value;
    _config.insert(std::pair<std::string, std::string>(key, value));
  }
  return 0;
}
  
std::string const & Config::getConfig(std::string const & key) {
  std::map<std::string,std::string>::iterator it;

  it = _config.find(key);
  if (it != _config.end()) {
    std::cout << key << " : " <<it->second << std::endl;
    return it->second;
  } 
  throw("Param not found in config file !");

}
