#include "audioengine.h"

AudioEngine::AudioEngine(){
}

const QStringList AudioEngine::outputDevices(){
    QStringList list;
    foreach(const QAudioDeviceInfo &deviceInfo, this->availableAudioInputDevices()){
        if(!deviceInfo.isNull())
        list << deviceInfo.deviceName();
    }
    return list;
}

const QStringList AudioEngine::inputDevices(){
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
