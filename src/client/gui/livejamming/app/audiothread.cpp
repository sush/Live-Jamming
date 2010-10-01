#include "audiothread.h"

#include <QDebug>

#include <iostream>
#include <stdexcept>

AudioThread::AudioThread() :
        client(NULL),
        options(JackNullOption),
        overruns(0),
        nb_ports(NB_CHANNELS),
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

void    AudioThread::start()
{

}

AudioThread::~AudioThread()
{
    jack_deactivate(client);
}
