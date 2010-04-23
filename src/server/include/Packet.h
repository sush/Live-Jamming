#ifndef __PACKET_H__
#define __PACKET_H__

#include <iostream>
#include <string.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>

#define sizeof_bin(A) sizeof(A) * 8

#define PACKET_MAXSIZE 2048
#define PROTO_VERSION_SIZE 4

typedef	unsigned int	field_t;

typedef struct {
  field_t proto : PROTO_VERSION_SIZE;
}bit_field;

class Packet
{
public:
  typedef boost::array<char, PACKET_MAXSIZE> buffer_t;

  Packet(boost::asio::ip::udp::endpoint *, buffer_t *, std::size_t);
  virtual ~Packet();

  int						getMaxSize() const;
  boost::asio::ip::udp::endpoint const &	getEndpoint() const;

  void						Print() const;
  buffer_t const &				getData() const;
  field_t					getProtoVersion() const;
  void						setProtoVersion(field_t);

protected:
  Packet(boost::asio::ip::udp::endpoint *);

  buffer_t *				_buffer;
  std::size_t				_len;
  boost::asio::ip::udp::endpoint *	_endpoint;
};

#endif // !__PACKET_H__
