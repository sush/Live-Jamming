#include "inputthread.h"
#include <stdexcept>

static int  jackProcess(jack_nframes_t nframes, void *arg ){
    InputThread *ip = static_cast<InputThread*> (arg);
    return ip->process(nframes);
}

int InputThread::process(jack_nframes_t nframes)
{
    if (can_process){
        jack_default_audio_sample_t* in[nb_ports];

        unsigned int chn;
        for (chn = 0; chn < nb_ports; chn++)
            in[chn] = static_cast<jack_default_audio_sample_t*>(jack_port_get_buffer (ports[chn], nframes));

        for (unsigned int i = 0; i < nframes; i++) {
            for (chn = 0; chn < nb_ports; chn++) {
                if (jack_ringbuffer_write (rb, reinterpret_cast<char*>((in[chn]+i)), SAMPLE_SIZE) < SAMPLE_SIZE)
                    overruns++;
            }
        }

        nb_pass++;
        mutex.tryLock();
        condition.wakeAll();
        mutex.unlock();
    }
    return 0;
}

InputThread::InputThread() : nb_pass(0), nb_pass_treat(0)
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
        sprintf (name, "input%d", i+1);
        ports[i] = jack_port_register(client, name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
        if(ports[i] == NULL)
            throw std::runtime_error(std::string("cannot register input port").append(name)); //trouvr un moyen de close le client
    }

    tmpPorts = jack_get_ports(client, 0, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput | JackPortIsPhysical);
    if (tmpPorts) {
        for (i=0;i<nb_ports && tmpPorts[i];i++) {
            qDebug() << jack_port_name(ports[i]);
            rv = jack_connect(client,tmpPorts[i],jack_port_name(ports[i]));
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

void    InputThread::run()
{
    forever {
        if ( !can_process ) {
            qDebug() << "CAN PROCESS GONE 0, INPUTTHREAD TERMINATING ! !\n";
            return ;//break ; //marche po !
        }
        mutex.lock();
        condition.wait(&mutex);
        //process audio compression
        //blah
        size_t toread = jack_ringbuffer_read_space(rb);

        //void*   buf;
        //size_t  size;
        if ((nb_pass_treat % 4) == 0)
            qDebug() << "audio proceed, nb_pass:" << nb_pass << nb_pass_treat;
        //jam->Send_jam(0, );
        nb_pass_treat++;
        mutex.unlock();
    }
    qDebug() << "CAN PROCESS GONE 0, INPUTTHREAD TERMINATING WITH REACHING END ! !";
}
