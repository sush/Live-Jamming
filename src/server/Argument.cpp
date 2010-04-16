#include "Argument.h"

Argument::Argument(int argc, char** const & argv) {
  BuildCommandLine(argc, argv);
}

Argument::~Argument() {}

int Argument::BuildCommandLine(int argc, char** const & argv) {
  boost::program_options::options_description desc("Usage: livejammin_server [options]\nAllowed options");
  desc.add_options()
    ("help,h", "produce help message")
    ("HostName,H", boost::program_options::value<std::vector<std::string> >(), "set server hostname")
    ("Port,p", boost::program_options::value<std::vector<std::string> >(), "set server port")
    ("BindAdress,b", boost::program_options::value<std::vector<std::string> >(), "set server bind(s) address(es)");
  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), _args);
  boost::program_options::notify(_args);
  
  if (_args.count("help")) {
    std::cout << desc << "\n";
    return 1;
  }
  return 0;
}

boost::program_options::variables_map Argument::getArgument() {
  return _args;
}
