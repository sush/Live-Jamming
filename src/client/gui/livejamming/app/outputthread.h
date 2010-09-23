#ifndef OUTPUTTHREAD_H
#define OUTPUTTHREAD_H

#include "audiothread.h"

class OutputThread : public AudioThread
{
public:
    OutputThread();
    bool    setPorts();
};

#endif // OUTPUTTHREAD_H
