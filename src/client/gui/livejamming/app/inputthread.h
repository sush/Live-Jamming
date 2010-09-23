#ifndef INPUTTHREAD_H
#define INPUTTHREAD_H
#include "audiothread.h"

class InputThread : public AudioThread
{
public:
    InputThread();
   void setPorts();
};

#endif // INPUTTHREAD_H
