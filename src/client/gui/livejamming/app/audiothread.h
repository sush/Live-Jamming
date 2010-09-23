#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QString>
#include <QDebug>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>

#include <jack/jack.h>
#include <jack/ringbuffer.h>

const int DEFAULT_RB_SIZE = 16384; //stolen from capture_client.c
const int NB_CHANNELS = 2;
const size_t SAMPLE_SIZE = sizeof(jack_default_audio_sample_t);

class AudioThread : public QThread
{
public:
    AudioThread();
    virtual void setPorts();
    //virtual int process(jack_nframes_t);

protected:
    QMutex    lock;
    QWaitCondition    ready;
    jack_nframes_t rb_size;
    jack_client_t *client;
    jack_port_t **ports;
    jack_ringbuffer_t *rb;
    jack_status_t status;
    jack_options_t options;
    unsigned int nb_ports;
    int bitdepth;
    long overruns;
    volatile int can_capture, can_process, rb_status;
    QString	    clientName,message;
};

#endif // AUDIOTHREAD_H
