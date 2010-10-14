#include "outputthread.h"
#include <stdexcept>

OutputThread::OutputThread()
{
}

void    OutputThread::setPorts(){
    unsigned short i;
    const QString portname("output_%1");
    const char	**tmpPorts;

   ports = new jack_port_t * [nb_ports];

    for (i=0;i < nb_ports;i++){
      ports[i] = jack_port_register(
                                               client,
                                               portname.arg(i+1).toUtf8().constData(),
                                               JACK_DEFAULT_AUDIO_TYPE,
                                               JackPortIsOutput,
                                               0
                                               );
      if(ports[i] == NULL)
          throw std::runtime_error("No more JACK output ports available");

      tmpPorts = jack_get_ports(client, 0, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput | JackPortIsPhysical);
      if (ports){
        for (i=0;i< nb_ports && ports[i];i++){
          jack_connect(client,jack_port_name(ports[i]),tmpPorts[i]);
        }
        ::free(tmpPorts);
      }
    }
}
