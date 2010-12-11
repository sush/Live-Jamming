#ifndef __AUDIOMIXINGENGINE_H__
#define __AUDIOMIXINGENGINE_H__

#include <iostream>
#include <vector>
#include <list>

class AudioMixingEngine;
class AudioFrame;
class MixingBuffer;
class ServerManager;
class Packet_v1_Jam;

#define AUDIOBUFFER_LEN		1024
#define MIXBUFFER_SIZE		10 // Number of frames to buffer during mix

#include <Room.h>

typedef float		audio_t;

class AudioMixingEngine
{
public :
  AudioMixingEngine(ServerManager *, Room *);
  virtual	~AudioMixingEngine();

  void		Mix(audio_t *, audio_t const *, std::size_t);
  void		recvAudioData(Packet_v1_Jam const *);
  std::size_t	getDropCount() const;

private:
  void		Init();

private:
  typedef std::list<AudioFrame *>		l_frame;	// list of frames (to keep everybody's frames
  typedef std::map<field_t, l_frame *>		m_frameList;

private:
  ServerManager *			_serverManager;
  Room *				_room;
  std::size_t				_size;

  Room::m_session const	*		_connected;
  m_frameList				_sepFrameMap;	// map containing everybody in the room's framelist 
  MixingBuffer *			_mixingBuffer;
};

#endif // ! __AUDIOMIXINGENGINE_H__
