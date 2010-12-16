#include "jackoutput.h"

#include <iostream>
#include <stdexcept>
#include <string.h>
#include <cstdio>

static int output_process(jack_nframes_t nframes, void *arg){
    JackOutput *output = static_cast<JackOutput*> (arg);
    jack_default_audio_sample_t *out, tmp[nframes * SAMPLE_SIZE];
                size_t toread;
    if ((toread = jack_ringbuffer_read_space(output->rb)) > (nframes * SAMPLE_SIZE))
    jack_ringbuffer_read(output->rb, (char *)tmp, nframes * SAMPLE_SIZE);
    for (unsigned int i=0;i<output->nb_ports;i++){
        if (output->isRunning()){
            output->mutex.lock();
           // if ((toread = jack_ringbuffer_read_space(output->rb)) > (nframes * SAMPLE_SIZE)){
//                qDebug() << "FILLED : " << (toread / (output->nb_ports * output->buffer_size * SAMPLE_SIZE)) << "/" << RB_MULTIPLICATOR;
//                qDebug() << "EMPTY  : " << jack_ringbuffer_write_space(output->rb) / (output->nb_ports * output->buffer_size * SAMPLE_SIZE) << "/" << RB_MULTIPLICATOR;
                out = (jack_default_audio_sample_t*)jack_port_get_buffer ( output->ports[i], nframes);
                memcpy(out, tmp,nframes * SAMPLE_SIZE );
            //}
            output->mutex.unlock();
        }else {
            //if jam is not running, just flush the output buffers
            out = (jack_default_audio_sample_t*)jack_port_get_buffer ( output->ports[i], nframes);
            for (unsigned int j=0; j < nframes;j++){
                out[j] = 0;
            }
        }
    }
    return 0;
}

void JackOutput::process(const char *audio){
    mutex.lock();
//  if ((size_t)jack_ringbuffer_read_space(rb) > (buffer_size * SAMPLE_SIZE * nb_ports))
//        jack_ringbuffer_reset(rb);
//   jack_ringbuffer_write(rb, audio, buffer_size * SAMPLE_SIZE * nb_ports);
    if ((size_t)jack_ringbuffer_read_space(rb) > (buffer_size * SAMPLE_SIZE))
          jack_ringbuffer_reset(rb);
     jack_ringbuffer_write(rb, audio, buffer_size * SAMPLE_SIZE);
   mutex.unlock();
}

JackOutput::JackOutput(){

    jack_set_process_callback(client, output_process, this);
    //jack_on_shutdown(client, shutdown, this);

    if (jack_activate(client) != 0)
        throw std::runtime_error("Could not activate jack");

    unsigned short i;
    ports = new jack_port_t* [nb_ports];

    for (i=0; i < nb_ports; i++) {
        char    name[64];
        sprintf (name, "output%d", i+1);
        ports[i] = jack_port_register(client, name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
        if(ports[i] == NULL)
            throw std::runtime_error(std::string("jack_port_register failed for port : ").append(name));
    }

    const char	**tmpPorts;

    tmpPorts = jack_get_ports(client, 0, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput | JackPortIsPhysical);
    if (tmpPorts) {
        for (i=0;i<nb_ports && tmpPorts[i];i++) {
            if(jack_connect(client,jack_port_name(ports[i]),tmpPorts[i]) != 0)
                throw std::runtime_error(std::string("jack_connect failed for port : ").append(jack_port_name(ports[i])));
        }
        jack_free(tmpPorts);
    }

    rb = jack_ringbuffer_create(nb_ports * buffer_size * SAMPLE_SIZE * RB_MULTIPLICATOR);
    memset(rb->buf, 0, rb->size);
}

JackOutput::~JackOutput(){
}
