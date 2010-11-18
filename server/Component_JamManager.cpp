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

  if (_audioBufferMap.find(jamId) == _audioBufferMap.end())
    _audioBufferMap.insert(std::pair<field_t, audio_t *>(jamId, new audio_t[AUDIOBUFFER_LEN / sizeof(audio_t)]));
  if (_audioBufferCountMap.find(jamId) == _audioBufferCountMap.end())
    _audioBufferCountMap.insert(std::pair<field_t, size_t>(jamId, 0));
  memset(_audioBufferMap.find(jamId)->second, 0, AUDIOBUFFER_LEN);
}

void	Component_JamManager::StopJam(field_t jamId)
{
  if (_jamMap->find(jamId) != _jamMap->end())
    _jamMap->erase(jamId);

  if (_audioBufferMap.find(jamId) != _audioBufferMap.end())
    _audioBufferMap.erase(jamId);
  if (_audioBufferCountMap.find(jamId) != _audioBufferCountMap.end())
    _audioBufferCountMap.erase(jamId);
}

void	Component_JamManager::Send_Jam(Session *session, audio_t const *audio)
{
  Packet_v1_Jam *packet_v1_jam = new Packet_v1_Jam(JAM_RECV);

  // pareil que commentaire de recv_jam, utilisez le type byte_t(qui est unsigned cahr)
  // plutot que char pcq comme c est du binaire ca risque d avoir des comportements bizarres si un octet depasse  127   // (voir arithmetique binaire complement a 2 si besoin precisions)

  packet_v1_jam->setAudio((byte_t const *)audio, AUDIOBUFFER_LEN);
  // !!!!!!!!!!!!!!!!!!!!!!! SET AUDIO DATALEN INSTEAD OF 400 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!! //

  _serverManager->Send(packet_v1_jam, session);
}

void	Component_JamManager::MixAudio(audio_t *audio_mixed, audio_t const *audio_channel, size_t len)
{
  for (size_t i = 0; i <len; ++i)
    audio_mixed[i] += audio_channel[i];
}

void	Component_JamManager::Send_Jam_Buffered(field_t jamId, audio_t const * audioBuffer)
{
  audio_t		*audio_mixed;
  size_t		audio_count;
  size_t		roomsize;

  audio_mixed = _audioBufferMap.find(jamId)->second;
  audio_count = ++_audioBufferCountMap.find(jamId)->second;
  roomsize  = _jamMap->find(jamId)->second->getRoom()->size();
  
  MixAudio(audio_mixed, audioBuffer, AUDIOBUFFER_LEN / sizeof(audio_t));
  if (audio_count >= roomsize)
    {
      Jam *jam = _jamMap->find(jamId)->second;
      std::map<field_t, Session*> *connected = jam->getRoom()->getConnected();
      std::map<field_t, Session*>::iterator it, end = connected->end();
      
      for (it = connected->begin(); it != end; ++it)
	Send_Jam(it->second, audio_mixed);
      memset(_audioBufferMap.find(jamId)->second, 0, AUDIOBUFFER_LEN);
      _audioBufferCountMap.find(jamId)->second = 0;

    }
  // mix audio with audio_save;
  // if count > jam size
  // send to all
  
}

void	Component_JamManager::Recv_Jam(Packet_v1 const *packet_v1, Session *session)
{
  session = session;
  Packet_v1_Jam const *packet_v1_jam = 
    static_cast<Packet_v1_Jam const *>(packet_v1);

  // j'ai caste et pas changer le type char * par byte_t *
  // partout pcq je voulais pas changer de type au cas ou c'etait utilise autre part
  audio_t const *audio			= (audio_t *)packet_v1_jam->getAudio(packet_v1_jam->getAudioDataLen());
  ////////////////////////////////////////////

  field_t jamId				= packet_v1_jam->getJamId();

  std::cout << "jamMap size :" <<  _jamMap->size() << std::endl;
  if (_jamMap->find(jamId) != _jamMap->end())
    {
      Jam *jam = _jamMap->find(jamId)->second;
      std::map<field_t, Session*> *connected = jam->getRoom()->getConnected();
      std::map<field_t, Session*>::iterator it, end = connected->end();
      
      //for (it = connected->begin(); it != end; ++it)
      //Send_Jam(it->second, audio);
      Send_Jam_Buffered(jamId, audio);
    }
}

void	Component_JamManager::Connect(Session *)
{}

void	Component_JamManager::Disconnect(Session *)
{}
