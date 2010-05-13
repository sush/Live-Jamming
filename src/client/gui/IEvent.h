#ifndef IEVENT_H
#define IEVENT_H

class Packet_v1;
class Session;

class IEvent
{
public:
    virtual         ~IEvent() {}
    virtual void    sessionEvent(Packet_v1 const*, Session*);
    virtual void    ChannelPacket(Packet_v1 const*, Session*);
};

#endif // IEVENT_H
