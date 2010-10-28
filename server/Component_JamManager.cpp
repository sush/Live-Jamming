#include <Component_JamManager.h>
#include <Bind_recv.h>

Component_JamManager::Component_JamManager(ServerManager *serverManager)
  :IComponent(JAM_COMPONENTID), _serverManager(serverManager)
{
  _jamMap = new m_jam();
}

Component_JamManager::~Component_JamManager()
{}

void	Component_JamManager::BindingsRecv()
{
  (*_bindingsRecv)[JAM_SEND] =
    new Bind_recv(this,static_cast<IComponent::pMethod>(&Component_JamManager::Recv_Jam));
}

void	Component_JamManager::RegisteredRequests()
{
  // SEND request
  (*_registeredRequests)[JAM_RECV] = 
    new Request(JAM_RECV, SEND, "JAM_RECV", NORETRY);

  // RECV requests
  (*_registeredRequests)[JAM_SEND] = 
    new Request(JAM_SEND, RECV, "JAM_SEND", RESPONSETONOTHING);
}

void	Component_JamManager::StartJam(field_t jamId, Room *room)
{
  if (_jamMap->find(jamId) == _jamMap->end())
    _jamMap->insert(std::pair<field_t, Jam*>(jamId, new Jam(room)));
}

void	Component_JamManager::StopJam(field_t jamId)
{
  if (_jamMap->find(jamId) != _jamMap->end())
    _jamMap->erase(jamId);
}

void	Component_JamManager::Send_Jam(Session *session, char const *audio, field_t clientSessionId)
{
  Packet_v1_Jam *packet_v1_jam = new Packet_v1_Jam(JAM_RECV);

  packet_v1_jam->setClientSessionId(clientSessionId);

  //pareil que commentaire de recv_jam, utilisez le type byte_t(qui est unsigned cahr) plutot que char pcq comme c est du binaire ca risque d avoir des comportements bizarres si un octet depasse  127 (voir arithmetique binaire complement a 2 si besoin precisions)
  packet_v1_jam->setAudio((byte_t const *)audio, 1024);	// !!!!!!!!!!!!!!!!!!!!!!! SET AUDIO DATALEN INSTEAD OF 400 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!! //

  _serverManager->Send(packet_v1_jam, session);
}

void	Component_JamManager::Recv_Jam(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Jam const *packet_v1_jam = 
    static_cast<Packet_v1_Jam const *>(packet_v1);

  // j'ai caste et pas changer le type char * par byte_t *
  // partout pcq je voulais pas changer de type au cas ou c'etait utilise autre part
  char const *audio			= (char const *)packet_v1_jam->getAudio(packet_v1_jam->getAudioDataLen());
  ////////////////////////////////////////////

  field_t clientSessionId		= session->getSessionId();
  field_t jamId				= packet_v1_jam->getJamId();

  if (_jamMap->find(jamId) != _jamMap->end())
    {
      Jam *jam = _jamMap->find(jamId)->second;
      std::map<field_t, Session*> *connected = jam->getRoom()->getConnected();
      std::map<field_t, Session*>::iterator it, end = connected->end();
      
      for (it = connected->begin(); it != end; ++it) {
	Send_Jam(it->second, audio, clientSessionId);
      }
    }
}

void	Component_JamManager::Connect(Session *)
{}

void	Component_JamManager::Disconnect(Session *)
{}
