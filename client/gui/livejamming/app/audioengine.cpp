#include "audioengine.h"
#include <QDebug>
#include <Packet.h>
#include <iostream>
#include <stdexcept>

class Component_Jam;

static int process(jack_nframes_t nframes,void *arg){
  AudioEngine *ip = static_cast<AudioEngine*> (arg);
  if (ip->isRunning()){
    unsigned int i;
    jack_default_audio_sample_t *in, *out;
    for ( i = 0; i < 1; i++ )
      {
	in = (jack_default_audio_sample_t*)jack_port_get_buffer ( ip->input_ports[i], nframes);
	ip->jam.Send_Jam((byte_t*)in, (field_t)nframes * sizeof ( jack_default_audio_sample_t ));
	//qDebug() << "SEND --> " << ((unsigned int*)in)[0] << " : " << ((unsigned int*)in)[1] << " : " << ((unsigned int*)in)[2] << " : " ;
	ip->mutex.lock();
	  if (jack_ringbuffer_read_space(ip->rb) > (nframes * sizeof ( jack_default_audio_sample_t ))){
	    char tmp[nframes*sizeof ( jack_default_audio_sample_t )];
	    out = (jack_default_audio_sample_t*)jack_port_get_buffer ( ip->output_ports[i], nframes);
	    jack_ringbuffer_read(ip->rb, tmp, nframes * sizeof ( jack_default_audio_sample_t ));
	    memcpy(out, tmp, nframes * sizeof ( jack_default_audio_sample_t ));
	  }
	ip->mutex.unlock();
      }
  }
  return 0;
}

int AudioEngine::processOutput(const char *audio){
  //qDebug() << "RECV --> " << ((unsigned int*)audio)[0] << " : " << ((unsigned int*)audio)[1] << " : " <<((unsigned int*)audio)[2] << " : " ;
  qDebug() << "Available Bytes" << jack_ringbuffer_write_space(rb);
  mutex.lock();
  jack_ringbuffer_write(rb, audio, buffer_size * sizeof ( jack_default_audio_sample_t ));
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
            throw std::runtime_error(std::string("cannot register input port").append(name));
    }
    for (i=0; i < nb_ports; i++) {
        char    name[64];
        sprintf (name, "output%d", i+1);
        output_ports[i] = jack_port_register(client, name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
        if(output_ports[i] == NULL)
            throw std::runtime_error(std::string("cannot register output port").append(name));
    }

    const char	**tmpPorts;

    tmpPorts = jack_get_ports(client, 0, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput | JackPortIsPhysical);
    if (tmpPorts) {
        for (i=0;i<nb_ports && tmpPorts[i];i++) {
            if (jack_connect(client,tmpPorts[i],jack_port_name(input_ports[i])) != 0)
                throw std::runtime_error("jack_connect");
        }
        jack_free(tmpPorts);
    }

    tmpPorts = jack_get_ports(client, 0, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput | JackPortIsPhysical);
    if (tmpPorts) {
        for (i=0;i<nb_ports && tmpPorts[i];i++) {
            if(jack_connect(client,jack_port_name(output_ports[i]),tmpPorts[i]) != 0)
                throw std::runtime_error("jack_connect");
        }
        jack_free(tmpPorts);
    }

    /*UGLY FIXED SIZE*/
    rb = jack_ringbuffer_create(nb_ports * buffer_size * sizeof(jack_default_audio_sample_t) * 4096);
    /*UGLY FIXED SIZE*/
    memset(rb->buf, 0, rb->size);
    running = true;
}

bool AudioEngine::isRunning(){
    return running;
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
  running = false;
  
  for(unsigned int i=0;i<nb_ports;i++){
    qDebug() << "DESTRUCT PORTS : " << i;
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
