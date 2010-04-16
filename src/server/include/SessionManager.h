#ifndef __SESSION_MANAGER_H__
#define __SESSION_MANAGER_H__

#include <iostream>
#include <boost/asio.hpp>


#include <Packet.h>
#include <Session.h>

class SessionManager
{
public:
  SessionManager();
  ~SessionManager();

  void		Manage(Packet *);



private:
  boost::asio::ip::udp::socket	*_socket
  

};



#endif // ! __SESSION_MANAGER_H__
