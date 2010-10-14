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
  packet_v1_jam->setAudio(audio);

  _serverManager->Send(packet_v1_jam, session);
}

void	Component_JamManager::Recv_Jam(Packet_v1 const *packet_v1, Session *session)
{
  Packet_v1_Jam const *packet_v1_jam = 
    static_cast<Packet_v1_Jam const *>(packet_v1);

  char const *audio			= packet_v1_jam->getAudio();
  field_t clientSessionId		= session->getSessionId();
  field_t jamId				= packet_v1_jam->getJamId();

  if (_jamMap->find(jamId) != _jamMap->end())
    {
      Jam *jam = _jamMap->find(jamId)->second;
      std::map<field_t, Session*> *connected = jam->getRoom()->getConnected();
      
      if (connected->find(clientSessionId) != connected->end())
	{
	  std::map<field_t, Session*>::iterator it, end = connected->end();
	  
	  for (it = connected->begin(); it != end; ++it)
	    Send_Jam(it->second, audio, clientSessionId);
	}
    }
}

void	Component_JamManager::Connect(Session *)
{}

void	Component_JamManager::Disconnect(Session *)
{}
