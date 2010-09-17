#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <cstdlib>
#include <iostream>

#include <jack/jack.h>

#include <QString>
#include <QDebug>

class AudioEngine
{
 public:
    AudioEngine();
    ~AudioEngine();

    /*
      PRIVATE METHODS
     */
 public:
    bool    init();
    bool    activate();
    void    deactivate();
    void    setCallbacks();
    void    connectPorts();
    int    process(jack_nframes_t);
    bool    registerPorts();
    void    close();
    /*
      PRIVATE VARIABLES
     */
 private:
    jack_client_t   *_jackClient;
    jack_options_t  _options;
    jack_status_t   _status;
    jack_port_t     **_iPorts;
    jack_port_t     **_oPorts;
        QString	    _clientName;
    unsigned short  _iChannels;

};

#endif // AUDIOENGINE_H
