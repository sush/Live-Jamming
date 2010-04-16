#ifndef __PACKET_H__
#define __PACKET_H__

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

#define PACKET_MAXSIZE 2048

class Packet
{
 public:
  typedef boost::array<char, PACKET_MAXSIZE> buffer_t;

  Packet(boost::asio::ip::udp::endpoint const *, buffer_t const *, std::size_t);
  virtual ~Packet();

  int						getMaxSize() const;
  boost::asio::ip::udp::endpoint const &	getEndpoint() const;

  void						Print() const;

 private:
  buffer_t const *				_buffer;
  std::size_t					_len;
  int						_maxSize;
  boost::asio::ip::udp::endpoint const *	_endpoint;
};

#endif // !__PACKET_H__
