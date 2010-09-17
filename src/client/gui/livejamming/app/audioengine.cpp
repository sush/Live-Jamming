#include "audioengine.h"

/*
  TODO :
  # throw error (std::runtime_error?)
  # In init(), match all available status error.


  */

AudioEngine::AudioEngine()
    : _options(JackNullOption),
    _iPorts(NULL),
    _oPorts(NULL),
    _clientName("LiveJamming"),
    _iChannels(2)
{
}

AudioEngine::~AudioEngine(){
    close();
}

/*
    STATIC METHODS FOR JACK CALLBACK
  */
static int  AudioEngine_process(jack_nframes_t nframes, void *arg ){
    AudioEngine *pAudioEngine = static_cast<AudioEngine *> (arg);  
    return pAudioEngine->process(nframes);
}

static void AudioEngine_shutdown(void *arg){
    std::cerr << "jack has shutdown" << std::endl;
    std::cerr.flush();
}

static void AudioEngine_error(const char *msg){
    std::cerr << "Jack : Error : " << msg << std::endl;
    std::cerr.flush();
}

static void AudioEngine_info(const char *msg){
    std::cerr << "Jack : Info : " << msg << std::endl;
    std::cerr.flush();
}


int    AudioEngine::processInput(jack_nframes_t nframes){
    int i;
    jack_default_audio_sample_t *in, *out;
    for (i = 0; i < _iChannels;i++){
        in = (jack_default_audio_sample_t*)jack_port_get_buffer ( _iPorts[i], nframes );
        out = (jack_default_audio_sample_t*)jack_port_get_buffer ( _oPorts[i], nframes );
        memcpy ( out, in, nframes * sizeof ( jack_default_audio_sample_t ) );
    }
    return 0;
}

int	AudioEngine::processOutput(){
  
}

void	AudioEngine::inputThread(){}
void	AudioEngine::outputThread(){}

bool	AudioEngine::init(){
    _jackClient = jack_client_open(_clientName.toUtf8().constData(), _options,&_status, NULL);

    if (_jackClient == NULL ||
        _status & JackServerFailed){
        qDebug() << "INIT ERROR";
        exit(1);
    }
    if(_status & JackServerStarted)
        qDebug() << "Jack server started";
    if(_status & JackNameNotUnique){
        _clientName = jack_get_client_name(_jackClient);
        qDebug() << "Unique name : "<< _clientName <<"assigned";
    }
    return true;
}

void    AudioEngine::setCallbacks(){
    jack_set_error_function(AudioEngine_error);
    jack_set_info_function(AudioEngine_info);
    jack_set_process_callback(_jackClient, AudioEngine_process, this);
    jack_on_shutdown(_jackClient, AudioEngine_shutdown, this);
}

bool	AudioEngine::registerPorts(){
    unsigned short i;
    const QString	portName("%1_%2");

    _iPorts = new jack_port_t * [_iChannels];
    _oPorts = new jack_port_t * [_iChannels];

    for (i = 0;i < _iChannels;i++){
        _iPorts[i] = jack_port_register(
                _jackClient,
                portName.arg("input").arg(i+1).toUtf8().constData(),
                JACK_DEFAULT_AUDIO_TYPE,
                JackPortIsInput,
                0
                );
        _oPorts[i] = jack_port_register(
                _jackClient,
                portName.arg("output").arg(i+1).toUtf8().constData(),
                JACK_DEFAULT_AUDIO_TYPE,
                JackPortIsOutput,
                0
                );
        if(_iPorts[i] == NULL || _oPorts[i] == NULL)
            qDebug() << "No more JACK ports available";//throw
    }
    return true;
}

void	AudioEngine::connectPorts(){
    unsigned short i;
    const char **ports;

    ports = jack_get_ports(_jackClient, 0, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput | JackPortIsPhysical);
    if (ports){
        for (i=0;i< _iChannels && ports[i];i++){
            jack_connect(_jackClient, jack_port_name(_oPorts[i]), ports[i]);
        }
        ::free(ports);
    }

    ports = jack_get_ports(_jackClient, 0, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput | JackPortIsPhysical);
    if (ports){
        for (i=0;i< _iChannels && ports[i];i++){
            jack_connect(_jackClient,ports[i],jack_port_name(_iPorts[i]));
        }
        ::free(ports);
    }
}

bool    AudioEngine::activate(){
    if (!jack_activate(_jackClient) == 0)
        return false;//throw
    return true;
}

void    AudioEngine::deactivate(){
    if(_jackClient)
        jack_deactivate(_jackClient);
}

void    AudioEngine::close(){
    if (_jackClient){
        unsigned short i;
        if(_iPorts){
            for (i=0;i<_iChannels && _iPorts[i];i++){
                jack_port_unregister(_jackClient, _iPorts[i]);
                _iPorts[i] = NULL;
            }
        }
        if(_oPorts){
            for (i=0;i<_iChannels && _oPorts[i];i++){
                jack_port_unregister(_jackClient, _oPorts[i]);
                _oPorts[i] = NULL;
            }
        }
        delete [] _iPorts;
        delete [] _oPorts;
        jack_client_close(_jackClient);
        _iPorts = NULL;
        _oPorts = NULL;
        _jackClient = NULL;
    }
}
