#ifndef __COMPONENT_CHANNELMANAGER_H__
#define __COMPONENT_CHANNELMANAGER_H__

class Component_ChannelManager;

#include <map>
#include <Server.h>
#include <IComponent.h>
#include <Protocol.h>
#include <Protocol_Channel.h>
#include <Packet_v1.h>
#include <Packet_v1_Channel.h>
#include <ServerManager.h>
#include <Channel.h>
#include <Session.h>

//! SERVER:  It is used to manage all the text base channels.

class Component_ChannelManager : public IComponent
{
  friend class Session;   // not needed ?

  friend class ServerManager;  // not needed ?

public:

  //! Default constructor.
  Component_ChannelManager(ServerManager *);
  //! Default destructor.
  virtual       ~Component_ChannelManager();

private:

  //! Bind received packet with associated method.
  virtual void  BindingsRecv();
  //! Register requests with protocol definition of channels packets
  virtual void	RegisteredRequests();
  
  //! Handle a channel Join request from a client.
  void          Recv_Join(Packet_v1 const *, Session *);

  //! Create a channel Join OK response to the client.
  void          Send_Join_OK(Session *, field_t, char const *);
  //! Create a channel Join NOK response to the client because already in channel.
  void          Send_Join_NOK_ALREADYINCHAN(Session *, field_t, char const *);
  //! Create a channel Joined response to the client, notification that a new user has joined the channel.
  void		Send_Joined(Session *, field_t, field_t, char const *);

  //! Handle Message request from a client.
  void          Recv_Message(Packet_v1 const *, Session *);
  //! Create a channel Message ACK response to the client in order to inform it that it's message has been received.
  void		Send_Message_ACK(Session *);
  //! Create a channel Message response to the client with the new message on the channel.
  void		Send_Message_RECV(Session *, char const *, field_t, field_t);

  //! Handle a leave request from a client.
  void          Recv_Leave(Packet_v1 const *, Session *);
  //! Create a channel Leave OK response to the client to inform it that it succesfuly leaved the channel.
  void          Send_Leave_OK(Session *, field_t);
  //! Create a channel Leave NOK response to the client to inform it that it failed to leave the channel.
  void          Send_Leave_NOK_NOTINCHAN(Session *, field_t);

  //! Create a channel Leaved response to the client to inform it that another client has leaved the channel.
  void		Send_Leaved(Session *, field_t, field_t, char const *);

  void		Connect(Session *);
  void		Disconnect(Session *);

  field_t	GenChannelId();
  bool		IsUniqId(field_t) const;

  ServerManager                         *_serverManager;
  typedef std::map<field_t, Channel*>	m_channel;
  m_channel				*_channelMap;
  boost::rand48				_rng;
};

#endif // ! __COMPONENT_CHANNELMANAGER_H__
