#include "Audio.h"

Audio::Audio()
{
  FMOD_MODE			mode = 
    FMOD_2D | FMOD_OPENUSER | FMOD_LOOP_NORMAL | FMOD_HARDWARE;
  FMOD_CREATESOUNDEXINFO	createsoundexinfo;
  int				numdrivers, count;
  int				channels = 2;

  _result = FMOD::System_Create(&_system);
  ERRCHECK(_result);

  _result = _system->setOutput(FMOD_OUTPUTTYPE_ALSA);
  ERRCHECK(_result);

  //  result = _system->setDriver(0);
  _result = _system->init(32, FMOD_INIT_NORMAL, 0);

  memset(&createsoundexinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
  createsoundexinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);              
  /* required. */
  createsoundexinfo.decodebuffersize  = 44100;                                /* Chunk size of stream update in samples. */
  /* This will be the amount of data passed to the user callback. */
  createsoundexinfo.length = 44100 * channels * sizeof(signed short) * 5;     /* Length of PCM data in bytes of whole song (for Sound::getLength) */
  createsoundexinfo.numchannels       = channels;                             /* Number of channels in the sound. */
  createsoundexinfo.defaultfrequency  = 44100;                                /* Default playback rate of sound. */
  createsoundexinfo.format            = FMOD_SOUND_FORMAT_PCM16;              /* Data format of sound. */

  _result = _system->createSound(0, mode, &createsoundexinfo, &_sound);
  ERRCHECK(_result);
}

Audio::~Audio(){}

void		Audio::ERRCHECK(FMOD_RESULT result)
{
  if (result != FMOD_OK)
    {
      std::cout << "ERROR (" << result << ") : " << FMOD_ErrorString(result) << std::endl;
      exit(-1);
    }
}

void		Audio::PlayOutput(FMOD::Sound *sound)
{
  FMOD::Channel *channel = 0;

  _result = _system->playSound(FMOD_CHANNEL_REUSE, sound, false, &channel);
  ERRCHECK(_result);
  int i = 400000;
  while(i > 0)
    {
      i--;
      _system->update();
    }
}

FMOD::Sound *		Audio::RecordInput()
{
  int driver = 0;

  _result = _system->recordStart(driver, _sound, false);
  ERRCHECK(_result);
  int i = 400000;
  while(i > 0)
    {
      i--;
      _system->update();
    }
  return _sound;
}
