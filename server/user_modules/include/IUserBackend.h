#ifndef __IUSERBACKEND_H__
#define __IUSERBACKEND_H__

#include <Singleton.h>
#include <string>
#include <vector>
#include <Manager.h>

//! SERVER:  Interface defines all mandatory method to get info from module.

template <typename T>
class IUserBackend : public Singleton<T> 
{
 public:


 public:
  //! Authentification method.
  /*! \param 1 string login */
  /*! \param 2 string password */
  virtual m_userinfo const *			Authentification(std::string const &, std::string const &) = 0;

  //! Get user friend list from module.
  /*! \param 1 int sessionId*/
  /*! \return m_userinfo with friend list */
  virtual std::vector<std::string> const &	getFriendList(std::string const &) = 0;
  virtual void					AddFriend(std::string const &, std::string const &) = 0;
  virtual void					DelFriend(std::string const &, std::string const &) = 0;
};

#endif
