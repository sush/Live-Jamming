#include "inputthread.h"

InputThread::InputThread()
{
}

bool	InputThread::setPorts(){
    unsigned short i;
    const QString portname("input_%1");
    const char	**tmpPorts;

    ports = new jack_port_t * [_channels];
    for (i=0;i < channels;i++){
      ports[i] = jack_port_register(
                                               client,
                                               portname.arg(i+1).toUtf8().constData(),
                                               JACK_DEFAULT_AUDIO_TYPE,
                                               JackPortIsInput,
                                               0
                                               );
      if(ports[i] == NULL)
       throw std::runtime_error("No more JACK input ports available");

      tmpPorts = jack_get_ports(client, 0, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput | JackPortIsPhysical);
      if (tmpPorts){
        for (i=0;i<channels && tmpPorts[i];i++){
          jack_connect(client,tmpPorts[i],jack_port_name(ports[i]));
        }
        ::free(tmpPorts);
      }
    }
}
