#ifndef __PACKET_V1_ROOM_H__
#define __PACKET_V1_ROOM_H__

class Manager;

#include <Packet_v1.h>
#include <Protocol.h>
#include <Protocol_Room.h>
#include <Room.h>


class Packet_v1_Room : public Packet_v1
{
 public :

  Packet_v1_Room(boost::asio::ip::udp::endpoint const *, buffer_t *, std::size_t);
  Packet_v1_Room(field_t);
  virtual               ~Packet_v1_Room();

  virtual void          Print(std::string const &, Manager const *) const;

  void                  setRoomId(field_t);
  field_t               getRoomId() const;

  void                  setClientSessionId(field_t);
  field_t               getClientSessionId() const;

  void                  setMessage(char const *);
  char const            *getMessage() const;

  void                  setRoomName(char const *);
  char const            *getRoomName() const;

  void                  setClientLogin(char const *);
  char const            *getClientLogin() const;

 protected:

  void                  Print_v1_Room(std::string const &, Manager const *) const;
};

#endif // ! __PACKET_V1_ROOM_H__
