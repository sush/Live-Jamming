#include <Component_Jam.h>
#include <Bind_recv.h>

Component_Jam::Component_Jam(ClientManager *clientManager)
  : IComponent(JAM_COMPONENTID), _clientManager(clientManager)
{}

Component_Jam::~Component_Jam() {}

void	Component_Jam::BindingsRecv()
{
    (*_bindingsRecv)[JAM_RECV] =
      new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Jam::Recv_Jam));
}

void	Component_Jam::RegisteredRequests()
{
  // SEND request
  (*_registeredRequests)[JAM_SEND] = 
    new Request(JAM_SEND, SEND, "JAM_SEND", NORETRY);

  // RECV requests
  (*_registeredRequests)[JAM_RECV] = 
    new Request(JAM_RECV, RECV, "JAM_RECV", RESPONSETONOTHING);
}

void	Component_Jam::StartJam(field_t jamId, Room *room)
{
  //    _audioEngine = new AudioEngine();
    //    _audioEngine->startRecording();
}

void	Component_Jam::StopJam(field_t jamId)
{
  //    delete _audioEngine;
}

void	Component_Jam::Recv_Jam(Packet_v1 const *packet_v1, Session *session)
{
    Packet_v1_Jam const *packet_v1_jam = 
    static_cast<Packet_v1_Jam const *>(packet_v1);

    // play audio stream packet_v1_jam->getAudio() sent by packet_v1_jam->getClientSessionId()
}

void	Component_Jam::Send_Jam(Session *session, char const *audio, field_t jamId)
{
  Packet_v1_Jam *packet_v1_jam = new Packet_v1_Jam(JAM_SEND);

  // boucle
  packet_v1_jam->setAudio(audio);
  _clientManager->Send(packet_v1_jam, session);
}

void	Component_Jam::Connect(Session *)
{}

void	Component_Jam::Disconnect(Session *)
{}
