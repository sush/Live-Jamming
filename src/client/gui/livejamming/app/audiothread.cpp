#include "audiothread.h"

#include <QDebug>

#include <iostream>
#include <stdexcept>

static int  jackProcess(jack_nframes_t nframes, void *arg ){
    AudioThread *at = static_cast<AudioThread *> (arg);
    return at->process(nframes);
}

static void jackShutdown(void *arg){
    std::cerr << "jack has shutdown" << std::endl;
    std::cerr.flush();
}

static void jackError(const char *msg){
    std::cerr << "Jack : Error : " << msg << std::endl;
    std::cerr.flush();
}

static void jackInfo(const char *msg){
    std::cerr << "Jack : Info : " << msg << std::endl;
    std::cerr.flush();
}

AudioThread::AudioThread() :
        client(NULL),
        nb_ports(NB_CHANNELS),
        clientName("live-jamming"),
        options(JackNullOption)
{
    client = jack_client_open(clientName.toUtf8().constData(), options,&status, NULL);

    if (client == NULL || status & JackServerFailed){
        throw std::runtime_error("Initialization of the Jack server Failed");
    }
    if(status & JackServerStarted)
      qDebug() << "Jack server started";
    if(status & JackNameNotUnique){
        clientName = jack_get_client_name(client);
        qDebug() << "Unique name : "+clientName +" assigned";
    }
    jack_set_error_function(jackError);
    jack_set_info_function(jackInfo);
    jack_set_process_callback(client, jackProcess, this);
    jack_on_shutdown(client, jackShutdown, this);

    if (!jack_activate(client) == 0)
        throw std::runtime_error("Could not activate jack");

    rb = jack_ringbuffer_create(nb_ports * DEFAULT_RB_SIZE * SAMPLE_SIZE);

//    _inputInfo.rb_size = DEFAULT_RB_SIZE;
//    _inputInfo.client = _jackClient;
//    _inputInfo._channels = _channels;
//    _inputInfo.can_process = 0;
//
//    rb = jack_ringbuffer_create (_channels * sizeof(jack_default_audio_sample_t) * _inputInfo.rb_size);
//    memset(_inputInfo.rb->buf, 0, rb->size);

}
