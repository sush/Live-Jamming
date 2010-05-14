#ifndef __IUSERBACKEND_H__
#define __IUSERBACKEND_H__

#include <Singleton.h>
#include <string>

//! SERVER:  Interface defines all mandatory method to get info from module.

template <typename T>
class IUserBackend : public Singleton<T> 
{
 public :

  typedef std::map<std::string, std::string>	m_userinfo;
  typedef m_userinfo::iterator			m_userinfo_it;
  typedef m_userinfo::const_iterator		m_userinfo_cit;
  typedef std::pair<std::string, std::string>	m_userinfo_pair;

  //! Authentification method.
  /*! \param 1 string login */
  /*! \param 2 string password */
  virtual bool					Authentification(std::string const &, std::string const &) = 0;
  //! Get user profile from module.
  /*! \param 1 int sessionId*/
  /*! \return m_userinfo with profil infos */
  virtual m_userinfo const			*getProfil(int) = 0;
  //! Get user friend list from module.
  /*! \param 1 int sessionId*/
  /*! \return m_userinfo with friend list */
  virtual m_userinfo const			*getFriendList(int) = 0;
};

#endif