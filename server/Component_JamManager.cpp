#include <Component_JamManager.h>
#include <Bind_recv.h>
#include <AudioMixingEngine.h>
#include <Exception.h>

Component_JamManager::Component_JamManager(ServerManager *serverManager)
  :IComponent(JAM_COMPONENTID), _serverManager(serverManager)
{
}

Component_JamManager::~Component_JamManager()
{
}

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
  assert(_jamMap.find(jamId) == _jamMap.end());
  assert(_audioMixingEngineMap.find(jamId) == _audioMixingEngineMap.end());
  
  _jamMap.insert(std::pair<field_t, Jam*>(jamId, new Jam(room)));
  _audioMixingEngineMap.insert(std::pair<field_t, AudioMixingEngine *>(jamId, new AudioMixingEngine(_serverManager, room)));
}

void	Component_JamManager::StopJam(field_t jamId)
{
  assert(_jamMap.find(jamId) != _jamMap.end());
  assert(_audioMixingEngineMap.find(jamId) != _audioMixingEngineMap.end());
  _jamMap.erase(jamId);
  std::cout << ">>>> jam DROPCount = " << _audioMixingEngineMap.find(jamId)->second->getDropCount() << std::endl;
  _audioMixingEngineMap.erase(jamId);
}


void	Component_JamManager::Recv_Jam(Packet_v1 const *packet_v1, Session *session)
{
  session = session;
  Packet_v1_Jam const *packet_v1_jam = 
    static_cast<Packet_v1_Jam const *>(packet_v1);
  field_t	jamId = packet_v1_jam->getJamId();

  if (_audioMixingEngineMap.find(jamId) == _audioMixingEngineMap.end())
    throw (X_BADJAM);
  _audioMixingEngineMap[jamId]->recvAudioData(packet_v1_jam);
}

void	Component_JamManager::Connect(Session *)
{}

void	Component_JamManager::Disconnect(Session *)
{}
