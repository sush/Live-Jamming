#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H
#include "engine.h"

#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QVBoxLayout>
#include <QTimer>
#include <QBuffer>
#include <QtMultimedia/qaudio.h>
#include <qdebug.h>

class FrequencySpectrum;
class Spectrograph;

class AudioEngine : public Engine
{
    Q_OBJECT;
public:
    AudioEngine();

    QStringList getIDevices();
    QStringList getODevices();
    const QAudioDeviceInfo& iDevice() const
                            {return this->m_audioInputDevice;}
    const QAudioDeviceInfo& oDevice() const
                            {return this->m_audioOutputDevice;}
    void startRecordAndPlayBack();
    void stopRecordAndPlayback();
};

#endif // AUDIOENGINE_H
