#include "audioengine.h"
/*
  CONSTRUCTOR/DESTRUCTOR
 */

AudioEngine::AudioEngine()
    : _options(JackNullOption),
    _clientName("Live-Jamming"),
    _activated(false),
    _iChannels(2)
{

}

AudioEngine::~AudioEngine(){
}

/*
    STATIC METHODS FOR JACK CALLBACK
  */
static int  AudioEngine_process(jack_nframes_t nframes, void *pvArg ){
}
static void AudioEngine_shutdown(void *pvArg){}
/*
  PRIVATE METHODS
 */
bool	AudioEngine::init(){
_jackClient = jack_client_open(_clientName, _options, NULL);

if (_jackClient == NULL ||
    _status & JackServerFailed)
    return false;
_clientName = jack_get_client_name(_jackClient);
return true;
}

void    AudioEngine::setCallbacks(){
    jack_set_process_callback(_jackClient, AudioEngine_process, this);
    jack_on_shutdown(_jackClient, AudioEngine_shutdown, this);
}

bool    AudioEngine::activate(){
    this->setCallbacks();
    if (!jack_activate(_jackClient) == 0)
        _activated = false;
    else
        _activated = true;
    return _activated;
}

void    AudioEngine::deactivate(){
    if(_jackClient)
        jack_deactivate(_jackClient);
}

void    AudioEngine::clean(){
    if (_jackClient){
        jack_client_close(_jackClient);
        _jackClient = NULL;
    }
}
