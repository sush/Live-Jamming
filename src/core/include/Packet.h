
#ifndef __PACKET_H__
#define __PACKET_H__

#include <iostream>
#include <string.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <Protocol.h>

#define sizeof_bin(A) sizeof(A) * 8
typedef unsigned char			      byte_t;

class Packet
{
public:
  typedef boost::array<byte_t, PACKET_MAXSIZE> buffer_t;

  Packet(boost::asio::ip::udp::endpoint const *, buffer_t *, std::size_t);
  virtual ~Packet();

  int						getMaxSize() const;
  boost::asio::ip::udp::endpoint const &	getEndpoint() const;

  void						Print() const;
  buffer_t const &				getRawData() const;
  field_t					getProtoVersion() const;
  void						setProtoVersion(field_t);

protected:
  Packet(boost::asio::ip::udp::endpoint const *);
  Packet();

protected:
  field_t					getField(unsigned int, unsigned int) const;
  void						setField(field_t, unsigned int, unsigned int);
  byte_t					*getData(unsigned int, unsigned int) const;
  void						setData(unsigned int, unsigned int, byte_t *);

  buffer_t *					_buffer;
  std::size_t					_len;
  boost::asio::ip::udp::endpoint const *       _endpoint;
};

#endif // !__PACKET_H__
