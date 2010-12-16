#include "jackinput.h"

#include <iostream>
#include <stdexcept>

static int input_process(jack_nframes_t nframes, void *arg){
    JackInput *input = static_cast<JackInput*> (arg);
    jack_default_audio_sample_t *in;
    if(input->isRunning()){
        jack_default_audio_sample_t toSend[SAMPLE_SIZE * nframes * input->nb_ports];
        for (unsigned int i = 0; i < input->nb_ports; i++ ){
            in = (jack_default_audio_sample_t*)jack_port_get_buffer ( input->ports[i], nframes);
            memcpy(toSend + ((i) * SAMPLE_SIZE * nframes), in, SAMPLE_SIZE * nframes);
        }
        input->jam.Send_Jam((byte_t*)toSend, (field_t)(nframes * SAMPLE_SIZE * input->nb_ports));
    }
    return 0;
}

JackInput::JackInput(Component_Jam&  jam_) :
        JackDefault(),
        jam(jam_)
{
    jack_set_process_callback(client, input_process, this);
    //jack_on_shutdown(client, shutdown, this);

    if (jack_activate(client) != 0)
        throw std::runtime_error("Could not activate jack");

    unsigned short i;

    for (i=0; i < nb_ports; i++) {
        char    name[64];
        sprintf (name, "input%d", i+1);
        ports[i] = jack_port_register(client, name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
        if(ports[i] == NULL)
            throw std::runtime_error(std::string("jack_port_register failed for port : ").append(name));
    }

    const char	**tmpPorts;

    tmpPorts = jack_get_ports(client, 0, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput | JackPortIsPhysical);
    if (tmpPorts) {
        for (i=0;i<nb_ports && tmpPorts[i];i++) {
            if (jack_connect(client,tmpPorts[i],jack_port_name(ports[i])) != 0)
                throw std::runtime_error(std::string("jack_connect failed for port : ").append(jack_port_name(ports[i])));
        }
        jack_free(tmpPorts);
    }
}

JackInput::~JackInput(){
}
