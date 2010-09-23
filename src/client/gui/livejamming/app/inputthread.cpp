#include "inputthread.h"

InputThread::InputThread()
{
}

void	InputThread::setPorts(){
    unsigned short i;
    const QString portname("%1_%2");
    const char	**ports;

    _ouputInfo.ports = new jack_port_t * [_channels];

    for (i=0;i < _channels;i++){
      _outputInfo.ports[i] = jack_port_register(
                                               _jackClient,
                                               portname.arg("output").arg(i+1).toUtf8().constData(),
                                               JACK_DEFAULT_AUDIO_TYPE,
                                               JackPortIsInput,
                                               0
                                               );
      if(_inputInfo.ports[i] == NULL){
        setMessage((QString)"No more JACK output ports available", true);
        return false;
      }

      ports = jack_get_ports(_jackClient, 0, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput | JackPortIsPhysical);
      if (ports){
        for (i=0;i< _channels && ports[i];i++){
          jack_connect(_jackClient,jack_port_name(_ouputInfo.ports[i]),ports[i]);
        }
        ::free(ports);
      }
    }
}
