#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QString>
#include <QDebug>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>

#include <jack/jack.h>
#include <jack/ringbuffer.h>

class AudioThread : public QThread
{
public:
    AudioThread();
    virtual void setPorts();

private:
    QMutex    lock;
    QWaitCondition    ready;
    jack_nframes_t rb_size;
    jack_client_t *client;
    jack_port_t **ports;
    jack_ringbuffer_t *rb;
    jack_status_t status;
    jack_options_t options;
    unsigned int channels;
    int bitdepth;
    long overruns;
    volatile int can_capture, can_process, status;
    QString	    clientName,message;

    virtual void jackInfo();
};

#endif // AUDIOTHREAD_H
