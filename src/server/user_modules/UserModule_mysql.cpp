#include <UserModule_mysql.h>

std::string const	&salt = "DYhG93b0qLive-JammingDIENOOBVoUubWwvniR2G0FgaC9mi";

UserModule_mysql::UserModule_mysql()
{
  Connection();
}

UserModule_mysql::~UserModule_mysql()
{}

void					UserModule_mysql::Connection()
{
  const char* db = "live-jamming_db", *server = "192.168.0.12", *user = "root", *pass = "MAgoun12$";
  
  _dbLink.set_option(new mysqlpp::MultiStatementsOption(true));
  _dbLink.connect(db, server, user, pass);
}

IUserBackend<UserModule_mysql>::m_userinfo const *	UserModule_mysql::Authentification(std::string const &login, std::string const &password)
{

  std::string request = "CALL PROC_GET_USERINFO("
    "(SELECT id FROM users WHERE login = '" +login+"' AND password = SHA1('" + salt + password + "')),"
   " 'fre');";
  
  mysqlpp::Query query = _dbLink.query(request);
  
  if (mysqlpp::StoreQueryResult res = query.store())
    {
      if (res.size() == 1)
	{
	  m_userinfo *				profil = new m_userinfo;
	  mysqlpp::Row::const_iterator	it, end = res[0].end();
	  int					i;

	  for (i = 0, it = res[0].begin(); it != end; ++it, ++i)
	    {
	      profil->insert(m_userinfo_pair(res.field_name(i), it->c_str()));
	    }
	  query.store_next();
	  return profil;
	}
      while (query.store_next());
      return 0;
    }
  else
    throw std::string("SQL server error: Unable to process SQL statement.");
  return 0;
}

std::vector<std::string> const &	UserModule_mysql::getFriendList(std::string const &login)
{
  std::vector<std::string> *friendList = new std::vector<std::string>();

  return *friendList;
}

//implement update friend list
