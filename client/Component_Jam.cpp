#include <Component_Jam.h>
#include <Bind_recv.h>
#include <QDebug>
#include "audioengine.h"

extern Session* gl_session;

Component_Jam::Component_Jam(ClientManager *clientManager)
    : IComponent(JAM_COMPONENTID), _clientManager(clientManager){
    try {
        _audioEngine = new AudioEngine(*this);
    } catch (std::exception &e){
        qDebug() << "Component_JAM :: " << e.what();
    }
}

Component_Jam::~Component_Jam() {
    delete _audioEngine;
}

void	Component_Jam::BindingsRecv(){
    (*_bindingsRecv)[JAM_RECV] =
            new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Jam::Recv_Jam));
}

void	Component_Jam::RegisteredRequests(){
    // SEND request
    (*_registeredRequests)[JAM_SEND] =
            new Request(JAM_SEND, SEND, "JAM_SEND", NORETRY);

    // RECV requests
    (*_registeredRequests)[JAM_RECV] =
            new Request(JAM_RECV, RECV, "JAM_RECV", RESPONSETONOTHING);
}

void	Component_Jam::StartJam(field_t jamId, Room *room){
    _jamId = jamId;
    _audioEngine->start();
    _sendCount = 0;
}

void	Component_Jam::StopJam(field_t jamId){
    _audioEngine->stop();
    _jamId = 0;
    _sendCount = 0;
}

void	Component_Jam::Recv_Jam(Packet_v1 const *packet_v1, Session *session){
    Packet_v1_Jam const *packet_v1_jam =
            static_cast<Packet_v1_Jam const *>(packet_v1);
    _audioEngine->output->process((const char*)packet_v1_jam->getAudio());
}

void	Component_Jam::Send_Jam(byte_t const *audio, field_t len){
    Packet_v1_Jam *packet_v1_jam = new Packet_v1_Jam(JAM_SEND);
    packet_v1_jam->setJamId(_jamId);
    packet_v1_jam->setTimestamp(++_sendCount);
    packet_v1_jam->setAudio(audio, len);
    _clientManager->Send(packet_v1_jam, gl_session);
}

void	Component_Jam::Connect(Session *){}

void	Component_Jam::Disconnect(Session *){}
