#ifndef __ROOM_H__
#define __ROOM_H__

#include <map>
#include <iostream>

#include <boost/threadpool.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <Session.h>

//! COMMON:  It is used to manage the list of channels and users connected.

class Room
{
 public:

  Room(char const *);
  virtual			~Room();

  std::map<field_t, Session *> *getConnected();

  bool                          addConnected(Session *, field_t);
  bool                          removeConnected(field_t);

  void                          setName(char const *);
  char const                    *getName() const;

 private:

  typedef std::map<field_t, Session*>   m_session;
  m_session                     *_connected;
  boost::mutex                  _room_mutex;
  std::string                  _name;
};

#endif // ! __ROOM_H__
