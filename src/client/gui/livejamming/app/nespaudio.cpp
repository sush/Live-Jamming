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

void NespAudio::startRecordAndPlayBack(){
    if(m_audioInput){
        if (QAudio::AudioInput == m_mode &&
            QAudio::SuspendedState == m_state) {
            m_audioInput->resume();
        } else {
            if (QAudio::AudioInput == m_mode &&
                QAudio::SuspendedState == m_state) {
                m_audioInput->resume();
            } else {
                m_audioInputIODevice = m_audioInput->start();
                m_audioOutput->start(m_audioInputIODevice);
            }
        }
    }
}

void NespAudio::stopRecordAndPlayback(){
    stopPlayback();
    stopRecording();
}
