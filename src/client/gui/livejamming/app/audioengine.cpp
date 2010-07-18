#include "audioengine.h"

AudioEngine::AudioEngine(){
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
