#ifndef __COMPONENT_CHANNEL_H__
#define __COMPONENT_CHANNEL_H__

class Component_Channel;
#include <iostream>
#include <IComponent.h>
#include <Packet_v1.h>
#include <Packet_v1_Channel.h>
#include <ClientManager.h>
#include <Protocol.h>
#include <Protocol_Channel.h>
#include <Session.h>
#include <Channel.h>

//! CLIENT: It is used to manage client interaction with channels.

class Component_Channel : public IComponent
{
public:

  //! Default constructor.
  Component_Channel(ClientManager *);
  //! Default destructor.
  virtual ~Component_Channel();

  //! Bind received packet with associated method.
  virtual void				BindingsRecv();
  //! Register requests with protocol definition of channels packets
  virtual void				RegisteredRequests();

  m_channel const &			getAllChannel() const;

private:


  //! Create a channel Join request to the server.
  void					Send_Join(Session *, field_t);
  //! Handle a channel Join OK request from the server to inform that the channel has been joined.
  void					Recv_Join_OK(Packet_v1 const *, Session *);

  //! Handle a channel Join NOK request from the server because client already leaved the channel.
  void					Recv_Join_NOK_ALREADYINCHAN(Packet_v1 const *, Session *);

  //! Handle a channel Joined request from server to inform that a new user has joined the channel
  void					Recv_Joined(Packet_v1 const *, Session *);
  //! Create a channel Join ACK request to the server in order to notify that the Joined request has been received.
  void					Send_Joined_ACK(Session *);

  //! Create a channel Message request to the server to send message to a chanel.
  void					Send_Message(Session *, char const *, field_t);
  //! Handle a channel Joined request from server to inform that a new user has joined the channel
  void					Recv_Message_RECV(Packet_v1 const *, Session *);

  //! Create a channel Message ACK request informing the server that message has been received.
  void					Send_Message_RECV_ACK(Session *);

  //! Create a channel Leave request in order to leave the channel.
  void					Send_Leave(Session *, field_t);
  //! Handle a channel Leave OK request from server to inform that channel has been leaved.
  void					Recv_Leave_OK(Packet_v1 const *, Session *);
  //! Handle a channel Leave NOK request from server to inform that channel has NOT been leaved because not in chan anymore.
  void					Recv_Leave_NOK_NOTINCHAN(Packet_v1 const *, Session *);
  
  //! Handle a channel Leavee request from server to inform that a client has leaved channel.
  void					Recv_Leaved(Packet_v1 const *, Session *);
  //! Create a channel Leaved ACK request in order to inform server that leaved notification has been rceived.
  void					Send_Leaved_ACK(Session *);
  
  ClientManager				*_clientManager;
  typedef std::map<field_t, Channel *>	m_channel;
  m_channel				_channelMap;
};

#endif
