#include <Argument.h>

Argument::Argument(int argc, char** const & argv) {
  BuildCommandLine(argc, argv);
}

Argument::~Argument() {}

int Argument::BuildCommandLine(int argc, char** const & argv) {

  boost::program_options::options_description desc("Usage: livejammin_server [options]\nAllowed options");

  try {
    desc.add_options()
      ("help,h", "produces help message")
      ("HostName,H", boost::program_options::value<std::vector<std::string> >(), "set server hostname")
      ("Port,p", boost::program_options::value<std::vector<std::string> >(), "set server port")
      ("BindAdress,b", boost::program_options::value<std::vector<std::string> >(), "set server bind(s) address(es)")
      ("Db,d", boost::program_options::value<std::vector<std::string> >(), "set database")
      ("DbServer,s", boost::program_options::value<std::vector<std::string> >(), "set database server address")
      ("DbSalt,S", boost::program_options::value<std::vector<std::string> >(), "set database salt")
      ("DbUser,u", boost::program_options::value<std::vector<std::string> >(), "set database user")
      ("DbPassword,P", boost::program_options::value<std::vector<std::string> >(), "set database password");
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), _args);
    boost::program_options::notify(_args);
    
    if (_args.count("help")) {
      std::cout << desc << "\n";
      exit(0);    
    }
  }
  catch (std::exception &e){
    std::cout << e.what() << "\n" << desc << std::endl;
    exit(1);
  }
  return 0;
}

boost::program_options::variables_map const & Argument::getArgument() const {
  return _args;
}
