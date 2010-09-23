#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <cstdlib>
#include <iostream>

#include "outputthread.h"
#include "inputthread.h"

class AudioEngine
{
 public:
    AudioEngine();
    ~AudioEngine();

 private:
    InputThread*    inputThread;
    OutputThread*   outputThread;
};

#endif // AUDIOENGINE_H
