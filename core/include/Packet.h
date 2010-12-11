#ifndef __PACKET_H__
#define __PACKET_H__

class Manager;

#include <iostream>
#include <string.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <Protocol.h>

#define PACKET_STRING "==================================="
#define PACKET_MAXSIZE 4096

typedef unsigned char			      byte_t;

#ifdef _DEBUG
extern int alloc_count;
extern int free_count;
#endif

class Packet
{
public:
  typedef boost::array<byte_t, PACKET_MAXSIZE> buffer_t;

  // this constructor is only useful for receive
  Packet(boost::asio::ip::udp::endpoint const *, buffer_t *, std::size_t);
  virtual					~Packet();

  int						getMaxSize() const;
  boost::asio::ip::udp::endpoint const &	getEndpoint() const;

  virtual void					Print(std::string const &, Manager const *) const;
  buffer_t const &				getRawData() const;
  field_t					getProtoVersion() const;
  void						setProtoVersion(field_t);
  void						setDeleteTTL(std::size_t);

  std::size_t					getLen() const;
  std::size_t					getDeleteTTL() const;
  void						decDeleteTTL();

protected:
						Packet(boost::asio::ip::udp::endpoint const *);
						Packet();
  field_t					getField(unsigned int, unsigned int) const;
  void						setField(field_t, unsigned int, unsigned int);
  byte_t					*getData(unsigned int, unsigned int) const;
  void						appendData(unsigned int, unsigned int, byte_t const *);
  void						setLen(std::size_t);
  void						addLen(std::size_t);

  void						setDataLen(field_t);
  field_t					getDataLen() const;
  static field_t				peekDataLen(Packet::buffer_t const &);

  byte_t					*getStartOfData(unsigned int, unsigned int) const;
  // not private anymore since audio data manipulation needs it

protected:
  void						Print_base() const;
  static field_t				peekField(Packet::buffer_t const &, unsigned int, unsigned int);



private:
  buffer_t *					_buffer;
  std::size_t					_len;
  boost::asio::ip::udp::endpoint const *        _endpoint;
  std::size_t					_ttl_delete;
};

#endif // !__PACKET_H__
