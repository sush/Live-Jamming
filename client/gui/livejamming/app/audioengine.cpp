#include "audioengine.h"
#include <QDebug>
#include <Packet.h>
#include <iostream>
#include <stdexcept>

class Component_Jam;

static int process(jack_nframes_t nframes,void *arg){
    jack_default_audio_sample_t *in, *out;
    AudioEngine *ae = static_cast<AudioEngine*> (arg);
    size_t toread;

    if (ae->isRunning()){
        for (int i = 0; i < 1; i++ )
        {
            in = (jack_default_audio_sample_t*)jack_port_get_buffer ( ae->input_ports[i], nframes);
            ae->jam.Send_Jam((byte_t*)in, (field_t)nframes * SAMPLE_SIZE);
            //qDebug() << "SEND --> " << ((unsigned int*)in)[0] << " : " << ((unsigned int*)in)[1] << " : " << ((unsigned int*)in)[2] << " : " ;
            ae->mutex.lock();
            if ((toread = jack_ringbuffer_read_space(ae->rb)) > (nframes * SAMPLE_SIZE)){
                qDebug() << "FILLED : " << (toread / (ae->nb_ports * ae->buffer_size * SAMPLE_SIZE)) << "/" << RB_MULTIPLICATOR;
                qDebug() << "EMPTY  : " << jack_ringbuffer_write_space(ae->rb) / (ae->nb_ports * ae->buffer_size * SAMPLE_SIZE) << "/" << RB_MULTIPLICATOR;
                char tmp[nframes*SAMPLE_SIZE];
                out = (jack_default_audio_sample_t*)jack_port_get_buffer ( ae->output_ports[i], nframes);
                jack_ringbuffer_read(ae->rb, tmp, nframes * SAMPLE_SIZE);
                memcpy(out, tmp, nframes * SAMPLE_SIZE);
            }
            ae->mutex.unlock();
        }
    } else {
        //if jam is not running, just flush the output buffer
        for (int i=0;i<1;i++){
            out = (jack_default_audio_sample_t*)jack_port_get_buffer ( ae->output_ports[i], nframes);
            for (unsigned int j=0; j < nframes;j++){
                out[j] = 0;
            }
        }
    }
    return 0;
}

int AudioEngine::processOutput(const char *audio){
  //qDebug() << "RECV --> " << ((unsigned int*)audio)[0] << " : " << ((unsigned int*)audio)[1] << " : " <<((unsigned int*)audio)[2] << " : " ;
  //qDebug() << "AVAILABLE BUFFER : " << jack_ringbuffer_write_space(rb) / (nb_ports *buffer_size * SAMPLE_SIZE);
  mutex.lock();
  jack_ringbuffer_write(rb, audio, buffer_size * SAMPLE_SIZE);
  mutex.unlock();
  return 0;
}

AudioEngine::AudioEngine(Component_Jam& jam_) :
        jam(jam_),
	client(NULL),
        options(JackNullOption),
        overruns(0),
        nb_ports(NB_CHANNELS),
        clientName("live-jamming"),
	running(false)
{
    client = jack_client_open(clientName, options, &status, NULL);
    if (client == NULL || status & JackServerFailed){
        throw std::runtime_error("Initialization of the Jack server Failed");
    }

    if (status & JackServerStarted )
        qDebug() << "Jack server started";

    if (status & JackNameNotUnique) {
        clientName = jack_get_client_name(client);
        qDebug() << "Unique name : " << clientName  << " assigned";
    }

    jack_set_process_callback(client, process, this);
    sample_rate = jack_get_sample_rate(client);
    buffer_size = jack_get_buffer_size(client);
    
    if (jack_activate(client) != 0)
        throw std::runtime_error("Could not activate jack");

    unsigned short i;
    input_ports = new jack_port_t* [nb_ports];
    output_ports = new jack_port_t* [nb_ports];

    for (i=0; i < nb_ports; i++) {
        char    name[64];
        sprintf (name, "input%d", i+1);
        input_ports[i] = jack_port_register(client, name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
        if(input_ports[i] == NULL)
            throw std::runtime_error(std::string("jack_port_register failed for port : ").append(name));
    }
    for (i=0; i < nb_ports; i++) {
        char    name[64];
        sprintf (name, "output%d", i+1);
        output_ports[i] = jack_port_register(client, name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
        if(output_ports[i] == NULL)
            throw std::runtime_error(std::string("jack_port_register failed for port : ").append(name));
    }

    const char	**tmpPorts;

    tmpPorts = jack_get_ports(client, 0, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput | JackPortIsPhysical);
    if (tmpPorts) {
        for (i=0;i<nb_ports && tmpPorts[i];i++) {
            if (jack_connect(client,tmpPorts[i],jack_port_name(input_ports[i])) != 0)
                throw std::runtime_error(std::string("jack_connect failed for port : ").append(jack_port_name(input_ports[i])));
        }
        jack_free(tmpPorts);
    }

    tmpPorts = jack_get_ports(client, 0, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput | JackPortIsPhysical);
    if (tmpPorts) {
        for (i=0;i<nb_ports && tmpPorts[i];i++) {
            if(jack_connect(client,jack_port_name(output_ports[i]),tmpPorts[i]) != 0)
                throw std::runtime_error(std::string("jack_connect failed for port : ").append(jack_port_name(output_ports[i])));
        }
        jack_free(tmpPorts);
    }

    /*UGLY FIXED SIZE*/
    rb = jack_ringbuffer_create(nb_ports * buffer_size * SAMPLE_SIZE * RB_MULTIPLICATOR);
    qDebug() << "RBSIZE : " << (rb->size / (nb_ports * buffer_size * SAMPLE_SIZE));
    /*UGLY FIXED SIZE*/
    memset(rb->buf, 0, rb->size);
}

bool AudioEngine::isRunning(){
    return running;
}

void AudioEngine::start(){
    running = true;
}

void AudioEngine::stop(){
    running = false;
    jack_ringbuffer_reset(rb);
}

void AudioEngine::celtCreate(){
    celt_mode = celt_mode_create(sample_rate, buffer_size, NULL);
    celt_encoder = celt_encoder_create(celt_mode, 1, NULL);
    celt_decoder = celt_decoder_create(celt_mode, 1, NULL);
}


void AudioEngine::celtDestroy(){
    celt_encoder_destroy(celt_encoder);
    celt_decoder_destroy(celt_decoder);
    celt_mode_destroy(celt_mode);
}

AudioEngine::~AudioEngine(){
    stop();

    for(unsigned int i=0;i<nb_ports;i++){
        jack_port_unregister(client,input_ports[i]);
        jack_port_unregister(client,output_ports[i]);
        input_ports[i] = NULL;
        output_ports[i] = NULL;
    }
    delete [] input_ports;
    delete [] output_ports;
    jack_deactivate(client);
    jack_client_close(client);
    input_ports = NULL;
    output_ports = NULL;
    client = NULL;
}
