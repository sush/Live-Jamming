#include "audiothread.h"

#include <QDebug>

#include <iostream>
#include <stdexcept>

AudioThread::AudioThread() :
        client(NULL),
        options(JackNullOption),
        overruns(0),
        nb_ports(NB_CHANNELS),
        can_process(0),
        clientName("live-jamming")

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

    rb = jack_ringbuffer_create(nb_ports * DEFAULT_RB_SIZE * SAMPLE_SIZE);
}

AudioThread::~AudioThread()
{
  /* FREE THE FUCKING RING BUFFER USING jack_ringbuffer_free()*/
    unsigned short i;
    for(i=0;i<nb_ports && ports[i];i++){
        qDebug() << "DESTRUCT PORTS : " << i;
        jack_port_unregister(client,ports[i]);
        ports[i] = NULL;
    }

    delete [] ports;
    jack_deactivate(client);
    jack_client_close(client);
    ports = NULL;
    client = NULL;
}
