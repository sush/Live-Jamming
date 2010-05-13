#ifndef EVENT_H
#define EVENT_H

#include "IEvent.h"

class Event : public IEvent
{
public:
    virtual void    sessionEvent(Packet_v1 const*, Session*);
    virtual void    channelEvent(Packet_v1 const*, Session*);
};

#endif // EVENT_H
