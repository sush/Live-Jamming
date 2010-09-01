#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <iostream>
#include <jack/jack.h>

class AudioEngine
{
 public:
    AudioEngine();
    ~AudioEngine();

    /*
      PRIVATE METHODS
     */
 private:
    bool    init();
    bool    activate();
    void    deactivate();
    void    setCallbacks();
    void    clean();
    /*
      PRIVATE VARIABLES
     */
 private:
    jack_client_t   *_jackClient;
    jack_options_t  _options;
    jack_status_t   _status;
    jack_port_t     **_iPorts;
    jack_port_t     **_oPorts;
    const char      *_clientName;
    bool            _activated;
    unsigned short  _iChannels;

};

#endif // AUDIOENGINE_H
