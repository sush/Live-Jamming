#include "nespaudio.h"

NespAudio::NespAudio(){
}

QStringList NespAudio::getODevices(){
    QStringList list;
    foreach(const QAudioDeviceInfo &deviceInfo, this->availableAudioInputDevices()){
        if(!deviceInfo.isNull())
        list << deviceInfo.deviceName();
    }
    return list;
}

QStringList NespAudio::getIDevices(){
    QStringList list;
    foreach(const QAudioDeviceInfo &deviceInfo, this->availableAudioInputDevices()){
        if(!deviceInfo.isNull())
        list << deviceInfo.deviceName();
    }
    return list;
}
