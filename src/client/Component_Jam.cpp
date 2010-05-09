#include <Component_Jam.h>

omponent_Jam::Component_Jam(IComponent::m_bindings_recv & bindingsRecv, ClientManager *clientManager)
  : IComponent(clientManager), _bindingsRecv(bindingsRecv), _clientManager(clientManager)
{
  BindingsRecv();
}

Component_Jam::~Component_Jam() {}

void            Component_Jam::BindingsRecv()
{
  _bindingsRecv[JAM_START] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Jam::Recv_Start));

  _bindingsRecv[JAM_OUTPUT] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Jam::Recv_Output));
   
  _bindingsRecv[JAM_STOP] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_Jam::Recv_Start));   
}

void	Component_Jam::Recv_Start(Packet_v1 *packet_v1){
  /*
    Init && test audio devices
    Gain Input;
    init input buffer
    chain to encode
    packet_v1->setData(buffer)
    _clientManager->send(packet_v1, session, NORETRY);
   */
}

void	Component_Jam::Recv_Input(Packet_v1 *packet_v1){
  /*decode && send data to output device*/
}

void	Component_Jam::Recv_Stop(Packet_v1 *packet_v1){
  /*Clean stream && shutdown device*/
}

void	Component_Jam::Send_Input(Packet_v1 *packet_v1, Session *session){
}
