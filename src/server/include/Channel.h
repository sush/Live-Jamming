#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include <Session.h>
#include <boost/thread.h>
#include <boost/threadpool.h>
#include <map>

class Channel
{
 public:
  Channel();
  Channel(Session*);
  ~Channel();
  
  std::vector<int> const & getConnected() const;
  
  bool			addConnected(Session*);
  bool			removeConnected(Session*);
  bool			isConnected(Session*);
  
private:
  
  std::map<Session*>	_connected;

  boost::mutex		_channel_mutex;
};

#endif // ! __CHANNEL_H__
