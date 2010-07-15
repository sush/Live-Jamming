#ifndef __PACKET_V1_H__
#define __PACKET_V1_H__

class Manager;

#include <iostream>
#include <boost/asio.hpp>

#include <Packet.h>

class Packet_v1 : public Packet
{
public:
  Packet_v1(boost::asio::ip::udp::endpoint const *, buffer_t *, std::size_t);
  Packet_v1(field_t, field_t);
  virtual		~Packet_v1();

  static field_t	peekComponentId(Packet::buffer_t const &);
  static field_t	peekRequestId(Packet::buffer_t const &);
  static field_t	peekDataLen(Packet::buffer_t const &);

  virtual void			Print(std::string const &, Manager const *) const;
  field_t		getRequestId() const;
  field_t		getComponentId() const;
  field_t		getSessionId() const;
  field_t		getDataLen() const;
  void			setRequestId(field_t);
  void			setComponentId(field_t);
  void			setSessionId(field_t);
  void			setDataLen(field_t);

protected:
  void			Print_v1(std::string const &, Manager const *) const;
  static field_t	peekField(Packet::buffer_t const &buffer, unsigned int, unsigned int);


};

#endif // ! __PACKET_V1_H__
