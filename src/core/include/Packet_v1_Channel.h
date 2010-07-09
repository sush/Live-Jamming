#ifndef __PACKET_V1_CHANNEL_H__
#define __PACKET_V1_CHANNEL_H__

#include <iostream>
#include <boost/asio.hpp>

#include <Packet_v1.h>
#include <Protocol.h>
#include <Protocol_Channel.h>
#include <Channel.h>

//! COMMON:  Defines methods to get datas from packet_v1 Channel type.

class Packet_v1_Channel : public Packet_v1
{
public:

  //! Constructor.
  /*! \param 1 field_t componentId */
  Packet_v1_Channel(field_t);
  //! Default destructor.
  virtual		~Packet_v1_Channel();

  //! Print packet.
  void			Print() const;
  //! Print packet_v1.
  void			Print_v1() const;

  //! Get channelId in the packet.
  /*! \return field_t channelId */
  field_t		getChannelId() const;
  //! Get clientSEssionId in the packet.
  /*! \return field_t clientSessionId */
  field_t		getClientSessionId() const;
  //! Set channelId in the packet.
  /*! \param 1 field_t channelId */
  void			setChannelId(field_t);
  //! Set clientSessionId in the packet.
  /*! \param 1 field_t clientSessionId */
  void			setClientSessionId(field_t);

  //! Set message in the packet.
  /*! \param 1 char * const  message */
  void			setMessage(char const *);
  //! Get message in the packet.
  /*! \return const char * message */
  char const		*getMessage() const;

  //! Set name of the channel in the packet.
  /*! \param 1 char * const  channel */
  void			setChannelName(char const *);
  //! Get channel name in the packet.
  /*! \return const char * channel */
  char const		*getChannelName() const;

  //! Set list of the channel in the packet.
  /*! \param 1 std::map<unsigned int, Channel*> const * m_channel */
  void			setChannelList(std::map<unsigned int, Channel*> *m_channel);
  //! Get channel list in the packet.
  /*! \return const char * channelList */
  std::vector<std::string>	*getChannelList() const;

private:
  
};

#endif // ! __PACKET_V1_CHANNEL_H__
