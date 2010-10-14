#ifndef OUTPUTTHREAD_H
#define OUTPUTTHREAD_H

#include "audiothread.h"

class OutputThread : public AudioThread
{
public:
    OutputThread();
    void    setPorts();
};

#endif // OUTPUTTHREAD_H
