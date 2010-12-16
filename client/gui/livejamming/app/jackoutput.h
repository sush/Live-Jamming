#ifndef JACKOUTPUT_H
#define JACKOUTPUT_H

#include <QMutex>

#include <jackdefault.h>
#include <jack/ringbuffer.h>

class JackOutput : public JackDefault
{
public:
    JackOutput();
    ~JackOutput();
    void process(const char*);
public:
    jack_ringbuffer_t *rb;
    QMutex mutex;

};

#endif // JACKOUTPUT_H
