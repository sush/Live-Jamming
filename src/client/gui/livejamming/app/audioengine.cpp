#include "audioengine.h"

AudioEngine::AudioEngine(){
}

QStringList AudioEngine::getODevices(){
    QStringList list;
    foreach(const QAudioDeviceInfo &deviceInfo, this->availableAudioInputDevices()){
        if(!deviceInfo.isNull())
        list << deviceInfo.deviceName();
    }
    return list;
}

QStringList AudioEngine::getIDevices(){
    QStringList list;
    foreach(const QAudioDeviceInfo &deviceInfo, this->availableAudioInputDevices()){
        if(!deviceInfo.isNull())
        list << deviceInfo.deviceName();
    }
    return list;
}

void AudioEngine::startRecordAndPlayBack(){
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

void AudioEngine::stopRecordAndPlayback(){
    stopPlayback();
    stopRecording();
}
