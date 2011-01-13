#ifndef __COMPONENT_JAMMANAGER_H__
#define __COMPONENT_JAMMANAGER_H__

class Component_JamManager;

#include <map>
#include <Server.h>
#include <IComponent.h>
#include <Protocol.h>
#include <Protocol_Jam.h>
#include <Packet_v1.h>
#include <Packet_v1_Jam.h>
#include <ServerManager.h>
#include <Session.h>
#include <Room.h>
#include <Jam.h>

#define AUDIOBUFFER_LEN 1024

class Component_JamManager : public IComponent
{
  friend class Session;
  friend class ServerManager;

 private:
  
  typedef float	audio_t;
  typedef std::map<field_t, size_t>	m_audioBuffer_count;
  typedef std::map<field_t, audio_t *>	m_audioBuffer;

 public:

  Component_JamManager(ServerManager *);
  virtual	~Component_JamManager();

  void		StartJam(field_t, Room*);
  void		StopJam(field_t);

 private:

  virtual void	BindingsRecv();
  virtual void	RegisteredRequests();

  void		Send_Jam(Session *, audio_t const *);
  void		Recv_Jam(Packet_v1 const *, Session *);

  void		Connect(Session *);
  void		Disconnect(Session *);

  typedef std::map<field_t, Jam *> m_jam;

  void		Send_Jam_Buffered(field_t, audio_t const *);
  void		MixAudio(audio_t *, audio_t const *, size_t);
  
private:

  m_jam			*_jamMap;
  m_audioBuffer		_audioBufferMap;
  m_audioBuffer_count	_audioBufferCountMap;
  ServerManager		*_serverManager;
};

#endif // ! __COMPONENT_JAMMANAGER_H__
