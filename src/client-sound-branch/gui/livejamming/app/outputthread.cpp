#include "outputthread.h"
#include <stdexcept>

static int  jackProcess(jack_nframes_t nframes, void *arg ){
    OutputThread *ip = static_cast<OutputThread*> (arg);
    return ip->process(nframes);
}

int OutputThread::process(jack_nframes_t nframes)
{
    if (can_process){
        //copy data from read buffer in the input port
    }
    return 0;
}

OutputThread::OutputThread() : nb_pass(0), nb_pass_treat(0)
{
    unsigned short i;
    const char	**tmpPorts;
    int rv;
    ports = new jack_port_t* [nb_ports];

    jack_set_process_callback(client, jackProcess, this);

    if (jack_activate(client) != 0)
        throw std::runtime_error("Could not activate jack");

    for (i=0; i < nb_ports; i++) {
        char    name[64];
        sprintf (name, "output%d", i+1);
        ports[i] = jack_port_register(client, name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
        if(ports[i] == NULL)
            throw std::runtime_error(std::string("cannot register output port").append(name)); //trouvr un moyen de close le client
    }

    tmpPorts = jack_get_ports(client, 0, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput | JackPortIsPhysical);
    if (tmpPorts) {
        for (i=0;i<nb_ports && tmpPorts[i];i++) {
            qDebug() << jack_port_name(ports[i]);
            rv = jack_connect(client,jack_port_name(ports[i]),tmpPorts[i]);
            if (rv != 0)
                throw std::runtime_error("jack_connect");
        }
        jack_free(tmpPorts);
    }
    /*Ports are registered and connected, process callback can process data*/
    can_process = 1;
    /*Tell Qthread to call run()*/
    start();
}


