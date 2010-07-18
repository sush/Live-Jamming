#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H
#include "engine.h"

#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QtMultimedia/qaudio.h>
#include <qdebug.h>

class AudioEngine : public Engine
{
    Q_OBJECT;
public:
    AudioEngine();

    const QStringList inputDevices();
    const QStringList outputDevices();
    const QAudioDeviceInfo& inputDevice() const
                            {return this->m_audioInputDevice;}
    const QAudioDeviceInfo& outputDevice() const
                            {return this->m_audioOutputDevice;}
    void startRecordAndPlayBack();
    void stopRecordAndPlayback();
};

#endif // AUDIOENGINE_H
