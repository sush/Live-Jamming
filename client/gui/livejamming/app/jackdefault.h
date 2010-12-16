#ifndef JACKDEFAULT_H
#define JACKDEFAULT_H

#include <jack/jack.h>

const int RB_MULTIPLICATOR = 64;
const unsigned int NB_CHANNELS = 2;
const size_t SAMPLE_SIZE = sizeof(jack_default_audio_sample_t);

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

#endif // JACKDEFAULT_H
