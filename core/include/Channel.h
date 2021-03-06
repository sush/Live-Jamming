#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include <boost/threadpool.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <Session.h>

#include <map>
#include <iostream>

//! COMMON:  It is used to manage the list of channels and users connected.

class Channel
{
 public:

  //! Default constructor.
  Channel(char const *);
  //! Default destructor.
  virtual ~Channel();
  
  //! Get map of all users connected to the channel indexed by sessionId.
  std::map<field_t, Session *> *getConnected();
  
  //! Add user to the channel.
  /*! \param 1 Session* of user */
  /*! \param 2 sessionId of user */
  /*! \return true if user has been added or false if not  */
  bool				addConnected(Session *, field_t);
  //! Remove user from the channel.
  /*! \param 1 sessionId of user */
  /*! \return true if user has been removed or false if not */
  bool				removeConnected(field_t);

  void				setName(char const *);
  char const			*getName() const;
  
private:

  typedef std::map<field_t, Session*>	m_session;    
  m_session			*_connected;
  boost::mutex			_channel_mutex;
  std::string			_name;
};

#endif // ! __CHANNEL_H__
