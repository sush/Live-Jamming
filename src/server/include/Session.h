#ifndef __SESSION_H__
#define __SESSION_H__

class Session;

#include <iostream>
#include <boost/asio.hpp>
#include <Packet.h>

class Session
{
public:
  Session(boost::asio::io_service const &, boost::asio::ip::udp, Packet const *);
  virtual				~Session();
  bool					operator == (Session const &) const;
  bool					operator == (Packet const &) const;

  boost::asio::ip::address		getIP() const;
  unsigned short			getPort() const;

private:
  boost::asio::io_service const &	_io_service;
  boost::asio::ip::address		_ip;
  unsigned short			_port;
};




#endif // ! __SESSION_H__
