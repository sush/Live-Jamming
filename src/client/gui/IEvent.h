#ifndef IEVENT_H
#define IEVENT_H

class Packet_v1;
class Session;

class IEvent
{
public:
    virtual         ~IEvent() = 0;
    virtual void    sessionEvent(Packet_v1 const*, Session*) = 0;
    virtual void    channelEvent(Packet_v1 const*, Session*) = 0;
};

inline IEvent::~IEvent() {}

#endif // IEVENT_H
