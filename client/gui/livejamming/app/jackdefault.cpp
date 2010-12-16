#include "jackdefault.h"
#include <QDebug>
#include <iostream>
#include <stdexcept>

JackDefault::JackDefault() :
        client(NULL),
        nb_ports(NB_CHANNELS),
        clientName("live-jamming"),
        options(JackNullOption),
        running(false)
{
    ports = new jack_port_t*[nb_ports];

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

    sample_rate = jack_get_sample_rate(client);
    buffer_size = jack_get_buffer_size(client);
}

JackDefault::~JackDefault(){
    for(unsigned int i=0;i<nb_ports;i++){
        jack_port_unregister(client,ports[i]);
        ports[i] = NULL;
    }
    delete [] ports;
    jack_deactivate(client);
    jack_client_close(client);
    ports = NULL;
    client = NULL;
}

void JackDefault::start(){
    running = true;
}
void JackDefault::stop(){
    running = false;
}
bool JackDefault::isRunning(){
    return running;
}
