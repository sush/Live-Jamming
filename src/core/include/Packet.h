#ifndef __PACKET_H__
#define __PACKET_H__

#include <iostream>
#include <string.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <Protocol.h>

#define sizeof_bin(A) sizeof(A) * 8

typedef	unsigned int	field_t;

class Packet
{
public:
  typedef unsigned char			      byte_t;
  typedef boost::array<byte_t, PACKET_MAXSIZE> buffer_t;

  Packet(boost::asio::ip::udp::endpoint *, buffer_t *, std::size_t);
  Packet(boost::asio::ip::udp::endpoint *);
  virtual ~Packet();

  int						getMaxSize() const;
  boost::asio::ip::udp::endpoint const &	getEndpoint() const;

  virtual void					Print() const;
  buffer_t const &				getData() const;
  field_t					getProtoVersion() const;
  void						setProtoVersion(field_t);

protected:
  field_t					getField(unsigned int, unsigned int) const;
  void						setField(field_t, unsigned int, unsigned int);

  buffer_t *				_buffer;
  std::size_t				_len;
  boost::asio::ip::udp::endpoint *	_endpoint;
};

#endif // !__PACKET_H__
