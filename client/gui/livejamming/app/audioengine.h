#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QString>
#include <QDebug>
#include <QMutex>

#include <jack/jack.h>
#include <jack/ringbuffer.h>
#include <celt/celt.h>

#include <Component_Jam.h>

const int RB_MULTIPLICATOR = 64;
const int NB_CHANNELS = 2;
const size_t SAMPLE_SIZE = sizeof(jack_default_audio_sample_t);

class Component_Jam;

class AudioEngine
{

 public:
    AudioEngine(Component_Jam&);
    ~AudioEngine();
    bool isRunning();
    int processOutput(const char*);
    void start();
    void stop();
 public:
    Component_Jam&  jam;
    /* jack stuff */
    jack_nframes_t buffer_size;
    jack_nframes_t sample_rate;
    jack_client_t *client;
    jack_port_t **input_ports;
    jack_port_t **output_ports;
    jack_status_t status;
    jack_options_t options;
    jack_ringbuffer_t *rb;
    QMutex mutex;
    long overruns;
    unsigned int nb_ports;
    int bitdepth;

    const char*   clientName;

 private:
    void	celtCreate();
    void	celtDestroy();
 private:
    bool	running;
    CELTMode	*celt_mode;
    CELTEncoder	*celt_encoder;
    CELTDecoder	*celt_decoder;
};

#endif // AUDIOENGINE_H
