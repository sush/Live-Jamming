#ifndef OUTPUTTHREAD_H
#define OUTPUTTHREAD_H

#include "audiothread.h"

class OutputThread : public AudioThread
{
public:
    OutputThread();
    void    processPacket(void* buf, size_t);
    int     process(jack_nframes_t nframes);
    void    run();
private:
    int nb_pass, nb_pass_treat;
    jack_ringbuffer_t*   intermediate_rb;
};

#endif // OUTPUTTHREAD_H
