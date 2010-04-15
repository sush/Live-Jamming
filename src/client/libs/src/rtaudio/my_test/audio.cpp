/*******************************************************/
/*
  @fileName audio.cpp
  @Author nespo_p

  Get & test default informations about sound devices
 */
/*******************************************************/

#include "RtAudio.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <map>


#if defined( __WINDOWS_ASIO__ ) || defined( __WINDOWS_DS__ )
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds ) 
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif


std::map<int, std::string> setMap(std::map<int, std::string> &apiMap){
  apiMap[RtAudio::MACOSX_CORE] = "OS-X Core Audio";
  apiMap[RtAudio::WINDOWS_ASIO] = "Windows ASIO";
  apiMap[RtAudio::WINDOWS_DS] = "Windows Direct Sound";
  apiMap[RtAudio::UNIX_JACK] = "Jack Client";
  apiMap[RtAudio::LINUX_ALSA] = "Linux ALSA";
  apiMap[RtAudio::LINUX_OSS] = "Linux OSS";
  apiMap[RtAudio::RTAUDIO_DUMMY] = "RtAudio Dummy";
  return apiMap;
}


int	main(int ac, char *argv[]) {
  
  RtAudio audio;
  RtAudio::DeviceInfo info;
  std::map<int, std::string> apiMap;
  std::vector< RtAudio::Api> apis;
  
  audio.showWarnings(true);
  RtAudio::getCompiledApi(apis);
  setMap(apiMap);
  
  std::cout << "\nCURRENT API = " << apiMap[ audio.getCurrentApi() ];
  std::cout << "\nCONNECTED DEVICE COUNT = " << audio.getDeviceCount();
  std::cout << "\nDEFAULT DEVICE IS = " << audio.getDefaultInputDevice();
  std::cout << "\nCURRENT DEVICE IS = " << audio.getDeviceCount() -1;
  
  try {
    info = audio.getDeviceInfo(audio.getDefaultInputDevice());
    std::cout << "\nDEFAULT DEVICE NAME = " << info.name;
    std::cout << "\nPROPED = " << info.probed;
    std::cout << "\nOUTPUT CHANNELS = " << info.outputChannels;
    std::cout << "\nINPUT CHANNELS = " << info.inputChannels;
    std::cout << "\nDUPLEX CHANNELS = " << info.duplexChannels;
    
  
  } catch (RtError& e){
        std::cout << '\n' << e.getMessage() << '\n' << std::endl;
  }
  return 1;
}
