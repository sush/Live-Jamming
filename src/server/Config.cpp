#include "Config.h"

Config::Config(std::string const & filename, int argc, char** const & argv) {
  BuildOption();
  UpdateOptionFromConfig(filename);
  UpdateOptionFromCommand(argc, argv);
  TraceOption();
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
  
std::string* Config::getValueFromConfig(std::string const & key) {
  std::map<std::string,std::string>::iterator it;

  it = _config.find(key);
  if (it != _config.end()) {
    return &it->second;
  } 
  else
    return NULL;
}

std::vector<std::string> Config::getValueFromCommand(std::string const & key) {
  std::vector<std::string> commands;

  if (_args.count(key)) {
    return _args[key].as< std::vector<std::string> >();
   }
  return commands;
}

void Config::BuildOption() {
  _options.insert(std::pair<std::string, Option*>("HostName", new Option("HostName", "-h", "-hostname", "1", true, std::vector<std::string>(1, "Live-Jamming"))));
  _options.insert(std::pair<std::string, Option*>("Port", new Option("Port", "-p", "-port", "1", true, std::vector<std::string>(1, "5042"))));
  _options.insert(std::pair<std::string, Option*>("BindAdress", new Option("BindAdress", "-b", "-bind", "1-", true, std::vector<std::string>(1, "0.0.0.0"))));
  Option *toto = _options["Port"];
  std::vector<std::string> test;
  test = toto->getValue();
  std::cout << "TEST = " << test.size() << std::endl;
}

void Config::UpdateOptionFromConfig(std::string const & filename) {
  OpenConfig(filename);
  BuildConfig();

  std::map<std::string, Option*>::iterator it;
  
  for (it=_options.begin(); it!=_options.end(); it++) {
    if (getValueFromConfig(it->first) != 0) {
      std::vector<std::string> configValue;
      configValue.push_back(*getValueFromConfig(it->first));
      Option *selectedOption = it->second;
      selectedOption->setValue(configValue);
    }
  }
}

void Config::UpdateOptionFromCommand(int argc, char** const & argv) {
  std::map<std::string, Option*>::iterator it;
  
  Argument *argument = new Argument(argc, argv);
  _args = argument->getArgument();

  for (it=_options.begin(); it!=_options.end(); it++) {
    if (!getValueFromCommand(it->first).empty()) {
      Option *selectedOption = it->second;
      selectedOption->setValue(getValueFromCommand(it->first));
    }
  }
}

Option* Config::getSelectedOption(std::string const & key) {
  return _options[key];
}

// trace Options value, to remove after
void Config::TraceOption() {
  std::map<std::string, Option*>::iterator it;

  for (it=_options.begin(); it!=_options.end(); it++) {
    std::cout << it->first << " = ";
    Option *selectedOption = it->second;
    std::vector<std::string> test = selectedOption->getValue();

    for (unsigned int i=0; i<test.size(); i++) {
      std::cout << test.at(i) << " ";
    }
    std::cout << "\n";
  }
}
