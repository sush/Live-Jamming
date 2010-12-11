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
const unsigned int NB_CHANNELS = 2;
const size_t SAMPLE_SIZE = sizeof(jack_default_audio_sample_t);

class Component_Jam;

class JackDefault
{
public:
    JackDefault();
    ~JackDefault();
    void start();
    void stop();
    bool isRunning();

public:
    jack_nframes_t buffer_size;
    jack_nframes_t sample_rate;
    jack_client_t *client;
    jack_port_t **ports;
    unsigned int nb_ports;

protected:
    const char  *clientName;
    jack_status_t status;
    jack_options_t options;

private:
    bool running;
};


class JackInput : public JackDefault
{
public:
    JackInput(Component_Jam&);
    ~JackInput();
    Component_Jam&  jam;
};

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

class AudioEngine
{

 public:
    AudioEngine(Component_Jam&);
    ~AudioEngine();
    void start();
    void stop();

 public:
    JackOutput  *output;
    JackInput   *input;

 private:
//    void	celtCreate();
//    void	celtDestroy();
    Component_Jam&  jam;

private:
    CELTMode	*celt_mode;
    CELTEncoder	*celt_encoder;
    CELTDecoder	*celt_decoder;
};













#endif // AUDIOENGINE_H
