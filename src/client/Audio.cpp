#include <Audio.h>

Audio::Audio(){}

Audio::~Audio(){}

void	Audio::ERRCHECK(FMOD_RESULT result){
  if (result != FMOD_OK){
    std::cout << "ERROR (" << result << ") : " << FMOD_ErrorString(result) << std::endl;
    exit(-1);
  }
    
}

void	Audio::Init(){
  FMOD_RESULT			result;
  FMOD_MODE               mode = FMOD_2D | FMOD_OPENUSER | FMOD_LOOP_NORMAL | FMOD_HARDWARE;
  FMOD_CREATESOUNDEXINFO  createsoundexinfo;
  int				numdrivers, count;
  int			channels = 2;
  FMOD::Channel          *channel = 0;

  result = FMOD::System_Create(&_system);
  ERRCHECK(result);
  result = _system->setOutput(FMOD_OUTPUTTYPE_ALSA);
  ERRCHECK(result);
  result = _system->init(32, FMOD_INIT_NORMAL, 0);
  memset(&createsoundexinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
  createsoundexinfo.cbsize            = sizeof(FMOD_CREATESOUNDEXINFO);              /* required. */
  createsoundexinfo.decodebuffersize  = 44100;                                       /* Chunk size of stream update in samples.  This will be the amount of data passed to the user callback. */
  createsoundexinfo.length            = 44100 * channels * sizeof(signed short) * 5; /* Length of PCM data in bytes of whole song (for Sound::getLength) */
  createsoundexinfo.numchannels       = channels;                                    /* Number of channels in the sound. */
  createsoundexinfo.defaultfrequency  = 44100;                                       /* Default playback rate of sound. */
  createsoundexinfo.format            = FMOD_SOUND_FORMAT_PCM16;                     /* Data format of sound. */


  result = _system->createSound(0, mode, &createsoundexinfo, &_sound);
  ERRCHECK(result);

  /*                                                                                                                                                                                                                            
        Play the sound.                                                                                                                                                                                                           
  */

  result = _system->playSound(FMOD_CHANNEL_FREE, _sound, 0, &channel);
  ERRCHECK(result);
  while(42){
    _system->update();
  }
}
