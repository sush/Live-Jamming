#include "audioengine.h"
#include <QDebug>
#include <Packet.h>
#include <iostream>
#include <stdexcept>

class Component_Jam;

AudioEngine::AudioEngine(Component_Jam& jam_):
        jam(jam_)
{
    output = new JackOutput();
    input = new JackInput(jam);
}

void AudioEngine::start(){
    input->start();
    output->start();
}

void AudioEngine::stop(){
    input->stop();
    output->stop();
}

//void AudioEngine::celtCreate(){
//    celt_mode = celt_mode_create(sample_rate, buffer_size, NULL);
//    celt_encoder = celt_encoder_create(celt_mode, 1, NULL);
//    celt_decoder = celt_decoder_create(celt_mode, 1, NULL);
//}


//void AudioEngine::celtDestroy(){
//    celt_encoder_destroy(celt_encoder);
//    celt_decoder_destroy(celt_decoder);
//    celt_mode_destroy(celt_mode);
//}

AudioEngine::~AudioEngine(){
    delete input;
    delete output;
}
/*
 JACK DEFAULT
 */
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

/*
 JACK INPUT
 */

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

/*
 JACK OUTPUT
 */
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
    //  celtCreate();
}

JackOutput::~JackOutput(){
}

