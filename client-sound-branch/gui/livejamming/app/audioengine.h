#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QString>
#include <QDebug>

#include <jack/jack.h>
#include <jack/ringbuffer.h>

const int DEFAULT_RB_SIZE = 16384; //stolen from capture_client.c
const int NB_CHANNELS = 2;
const size_t SAMPLE_SIZE = sizeof(jack_default_audio_sample_t);

class Component_Jam;

class AudioEngine
{

 public:
    AudioEngine(Component_Jam&);
    ~AudioEngine();
    //static int process(jack_nframes_t, void*);
    bool running();

 public:
    Component_Jam&  jam;
    bool    _running;
    /* jack stuff */
    jack_nframes_t rb_size;
    jack_client_t *client;
    jack_port_t **input_ports;
    jack_port_t **output_ports;
    jack_ringbuffer_t *rb;
    jack_status_t status;
    jack_options_t options;
    long overruns;
    unsigned int nb_ports;
    int bitdepth;
    const char*   clientName;
};

#endif // AUDIOENGINE_H
