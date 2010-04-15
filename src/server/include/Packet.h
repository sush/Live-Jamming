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

  Packet(buffer_t const *, std::size_t);
  virtual ~Packet();

  void	Print() const;
  int	getMaxSize() const;

 private:
  buffer_t const *		_buffer;
  std::size_t			_len;
  int				_maxSize;

};

#endif // !__PACKET_H__
