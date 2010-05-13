#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include <Session.h>
#include <map>

class Channel
{
 public:

  Channel();
  virtual ~Channel();
  
  std::map<field_t, Session *> const & getConnected() const;
  
  bool				addConnected(Session *, field_t);
  bool				removeConnected(field_t);
  
private:
  
  std::map<field_t, Session*>	_connected;
  boost::mutex			_channel_mutex;
};

#endif // ! __CHANNEL_H__
