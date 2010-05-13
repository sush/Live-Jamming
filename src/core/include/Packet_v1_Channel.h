#ifndef __PACKET_V1_CHANNEL_H__
#define __PACKET_V1_CHANNEL_H__

#include <iostream>
#include <boost/asio.hpp>

#include <Packet_v1.h>
#include <Protocol.h>
#include <Protocol_Channel.h>

class Packet_v1_Channel : public Packet_v1
{
public:
  Packet_v1_Channel(field_t);
  virtual		~Packet_v1_Channel();

  void			Print() const;
  void			Print_v1() const;

  field_t		getChannelId() const;
  field_t		getClientSessionId() const;
  void			setChannelId(field_t);
  void			setClientSessionId(field_t);

  void			setMessage(char const *);
  char const		*getMessage() const;

private:
  
};

#endif // ! __PACKET_V1_CHANNEL_H__
