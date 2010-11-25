#ifndef __PACKET_V1_JAM_H__
#define __PACKET_V1_JAM_H__

class Manager;

#include <Packet_v1.h>
#include <Protocol.h>
#include <Protocol_Jam.h>
#include <Jam.h>


class Packet_v1_Jam : public Packet_v1
{
 public :

  Packet_v1_Jam(boost::asio::ip::udp::endpoint const *, buffer_t *, std::size_t);
  Packet_v1_Jam(field_t);
  virtual               ~Packet_v1_Jam();

  virtual void          Print(std::string const &, Manager const *) const;

  void                  setJamId(field_t);
  field_t               getJamId() const;

  void                  setClientSessionId(field_t);
  field_t               getClientSessionId() const;

  void                  setAudioDataLen(field_t); // field_t cannot exceed PROTOV1_JAM_AUDIODATALEN_SIZE len
						  //(ex if PROTOV1_JAM_AUDIODATALEN_SIZE = 16, field_t cannot exceed 65535)
  field_t               getAudioDataLen() const;

  void			setMixCount(field_t);
  field_t		getMixCount() const;


  void                  setAudio(byte_t const *, field_t);
  byte_t const            *getAudio(field_t) const;

 protected:

  void                  Print_v1_Jam(std::string const &, Manager const *) const;
};

#endif // ! __PACKET_V1_JAM_H__
