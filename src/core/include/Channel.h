#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include <Session.h>
#include <map>

//! COMMON:  It is used to manage the list of channels and users connected.

class Channel
{
 public:

  //! Default constructor.
  Channel();
  //! Default destructor.
  virtual ~Channel();
  
  //! Get map of all users connected to the channel indexed by sessionId.
  std::map<field_t, Session *> const & getConnected() const;
  
  //! Add user to the channel.
  /*! \param 1 Session* of user */
  /*! \param 2 sessionId of user */
  /*! \return true if user has been added or false if not  */
  bool				addConnected(Session *, field_t);
  //! Remove user from the channel.
  /*! \param 1 sessionId of user */
  /*! \return true if user has been removed or false if not */
  bool				removeConnected(field_t);
  
private:
  
  std::map<field_t, Session*>	_connected;
  boost::mutex			_channel_mutex;
};

#endif // ! __CHANNEL_H__
