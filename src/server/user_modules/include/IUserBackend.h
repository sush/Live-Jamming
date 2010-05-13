#ifndef __IUSERBACKEND_H__
#define __IUSERBACKEND_H__

#include <Singleton.h>
#include <string>

template <typename T>
class IUserBackend : public Singleton<T> {

 public :

  typedef std::map<std::string, std::string> m_userinfo;
  typedef m_userinfo::iterator m_userinfo_it;
  typedef m_userinfo::const_iterator m_userinfo_cit;
  typedef std::pair<std::string, std::string> m_userinfo_pair;

  virtual bool			 Authentification(std::string const &, std::string const &) = 0;
  virtual m_userinfo const	*getProfil(int) = 0;
  virtual m_userinfo const	*getFriendList(int) = 0;
};

#endif
