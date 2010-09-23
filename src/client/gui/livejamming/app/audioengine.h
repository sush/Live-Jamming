#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include "outputthread.h"
#include "inputthread.h"

#include <jack/ringbuffer.h>

class AudioEngine
{
 public:
    AudioEngine();
    ~AudioEngine();

 private:
    InputThread*    inputThread;
    OutputThread*   outputThread;
    jack_ringbuffer_t*  rb;
};

#endif // AUDIOENGINE_H
