#ifndef INPUTTHREAD_H
#define INPUTTHREAD_H
#include "audiothread.h"

class InputThread : public AudioThread
{
public:
    InputThread();
    int process(jack_nframes_t);
    void    run();

private:
    unsigned int nb_pass;
};

#endif // INPUTTHREAD_H
