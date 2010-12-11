//
//
//
//        NOW MAKE THIS CLASS COMPLETELY THREAD SAFE
//
//
//
//	ACHIEVED THIS BY DEALING WITH THE ONLY PUBLIC FCTN really needing locking : pushFrame
//           N O W   T E S T   I T   ! ! !

#ifndef __MIXINGBUFFER_H__
#define __MIXINGBUFFER_H__

#include <iostream>
#include <boost/thread.hpp>

class MixingBuffer;
class ServerManager;
class Room;

#define	AUDIOBUFFER_MAXLEN	1024

#include <AudioFrame.h>

class MixingBuffer
{
public:
			MixingBuffer(ServerManager *, Room *, std::size_t);
  virtual		~MixingBuffer();
  void			pushFrame(AudioFrame const *);
  std::size_t		getDropCount() const;

private:
  void			InitBuffer();
  void			ResetOne(std::size_t);
  void			ResetAll();
  void			Mix(std::size_t, AudioFrame const *);
  bool			IsMixed(AudioFrame const *, std::size_t) const; // is a frame from that participant already mixed at the  buffer pos given
  void			DropFrame(AudioFrame const *);
  std::size_t		FindPosition(AudioFrame const *audioFrame) const; //find pos to mix frame (based on timestamp)
  std::size_t		CountMixed(std::size_t) const; // number of participants that have audio data mixed at that pos
  void			SendFrameToRoom(std::size_t idx);
  void			Debug_Print() const;
    
private:
  typedef std::map<unsigned int, std::size_t>		m_participants;
  // map of sessionId timestamp (0 if no frame of such user)

  typedef struct
  {
    m_participants		_participantsMap;
    audioData_t			_mixData[AUDIOBUFFER_MAXLEN];
    std::size_t			_len;
  }mixframe_container;

  private:
  ServerManager *		_serverManager;
  mixframe_container *		_mixBuffer;
  Room *			_room;
  std::size_t			_size; // number of frames contained by mixbuffer 
  std::size_t			_drop; // number of dropped frames so far

  // ringBuffer 
  std::size_t			_start; 
  std::size_t			_end;
  std::size_t			_count; // number of currently used elements
  boost::mutex			_mixMutex;
};

#endif // ! __MIXINGBUFFER_H__
