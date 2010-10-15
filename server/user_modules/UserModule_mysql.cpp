#include <UserModule_mysql.h>
#include <stdexcept>

UserModule_mysql::UserModule_mysql()
{}

UserModule_mysql::~UserModule_mysql()
{}

void			UserModule_mysql::Connection(char const *db, char const *server, char const *salt, char const *user, char const *pass)
{
  _salt = salt;
 
  _dbLink.set_option(new mysqlpp::MultiStatementsOption(true));
  _dbLink.connect(db, server, user, pass);
}

m_userinfo const *	UserModule_mysql::Authentification(std::string const &login, std::string const &password)
{
  mysqlpp::Query query = _dbLink.query();
  query << "CALL PROC_GET_USERINFO(""(SELECT id FROM users WHERE login = \"" << mysqlpp::escape << login << "\" AND password = SHA1(\"" << mysqlpp::escape << (_salt + password) << "\")),"
    " 'fre');";
  
  if (mysqlpp::StoreQueryResult res = query.store())
    {
      if (res.size() == 1)
	{
	  m_userinfo *				profil = new m_userinfo;
	  mysqlpp::Row::const_iterator	it, end = res[0].end();
	  int					i;

	  for (i = 0, it = res[0].begin(); it != end; ++it, ++i)
	    profil->insert(m_userinfo_pair(res.field_name(i), it->c_str()));
	  query.store_next();
	  return profil;
	}
      while (query.store_next());
      return 0;
    }
  else
    throw std::runtime_error("SQL server error: Unable to process SQL statement.");
  return 0;
}

std::vector<std::string> const &	UserModule_mysql::getFriendList(std::string const &login)
{
  std::vector<std::string> *friendList = new std::vector<std::string>();

  std::string request	= "CALL PROC_GET_FRIENDLIST_LOGIN('"+login+"');";
  mysqlpp::Query query	= _dbLink.query(request);

  if (mysqlpp::StoreQueryResult res = query.store())
    {
      if (res.size() > 0)
	{
	  for (unsigned int i = 0; i < res.size(); ++i)
	    {
	      mysqlpp::Row::const_iterator	it, end = res[i].end();
	      int j;
	      for (j = 0, it = res[i].begin(); it != end; ++it, ++j)
		friendList->push_back(it->c_str());
	    }
	  query.store_next();
	}
      while (query.store_next());
    }
  return *friendList;
}

void					UserModule_mysql::AddFriend(std::string const &login, std::string const &friendLogin)
{
  std::string request	= "CALL PROC_ADD_FRIEND_LOGIN('"+login+"','"+friendLogin+"');";
  mysqlpp::Query query	= _dbLink.query(request);

  if (mysqlpp::StoreQueryResult res = query.store())
    while (query.store_next());
}

void					UserModule_mysql::DelFriend(std::string const &login, std::string const &friendLogin)
{
  std::string request	= "CALL PROC_DEL_FRIEND_LOGIN('"+login+"','"+friendLogin+"');";
  mysqlpp::Query query	= _dbLink.query(request);

  if (mysqlpp::StoreQueryResult res = query.store())
    while (query.store_next());
}
