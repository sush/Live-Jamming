#ifndef __AUDIOMIXINGENGINE_H__
#define __AUDIOMIXINGENGINE_H__

class AudioMixingEngine;

#include <iostream>
#include <vector>
#include <list>

#define AUDIOBUFFER_LEN		1024
#define MIXBUFFER_SIZE		10 // Number of frames to buffer during mix

#include <Room.h>

typedef float		audio_t;

class AudioMixingEngine
{
public :
		AudioMixingEngine();
  virtual	~AudioMixingEngine();

  void		Mix(audio_t *, audio_t const *, std::size_t);
  void		AddFrame(audio_t *);

private:
  typedef std::list<audio_t *>		l_frame;	// list of frames (to keep everybody's frames

  typedef std::map<field_t, bool>	m_participants;	// list of sessionId and bool to see
							// who is present in the mixed stream
  // user's sessionid + framelist
  typedef struct frame_container	
  {
    field_t	_sessionId;
    l_frame	_frameList;
  };
  typedef std::map<field_t, l_frame *>	m_frameList;

  typedef struct mixframe_container
  {
    m_participants		_participantsMap;
    audio_t[AUDIOBUFFER_LEN]	_mixframe;
  };


private:
  std::size				_size;

  Room::m_session const	*		_connected;
  m_frameList				_sepFrameMap;	// map containing everybody in the room's framelist 
  mixframe_container *			_mixBuffer;		// mixframe buffer
  std::size_t				_mixBufferCount;	// how many frames are there in the mixbuffer

};

#endif // ! __AUDIOMIXINGENGINE_H__
