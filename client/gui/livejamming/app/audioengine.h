#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

class OutputThread;
class InputThread;

#include <jack/ringbuffer.h>

class Component_Jam;

class AudioEngine
{
 public:
    AudioEngine(Component_Jam&);
    ~AudioEngine();

 private:
    Component_Jam&  jam;
    InputThread*    inputThread;
    OutputThread*   outputThread;
    bool    running;
};

#endif // AUDIOENGINE_H
