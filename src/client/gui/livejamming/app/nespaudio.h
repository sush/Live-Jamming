#ifndef NESPAUDIO_H
#define NESPAUDIO_H
#include "engine.h"

#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioFormat>
#include <qdebug.h>
#include <QTimer>
#include <QBuffer>

class FrequencySpectrum;

class NespAudio : public Engine
{
    Q_OBJECT;
public:
    NespAudio();

    QStringList getIDevices();
    QStringList getODevices();
    const QAudioDeviceInfo& iDevice() const
                            {return this->m_audioInputDevice;}
    const QAudioDeviceInfo& oDevice() const
                            {return this->m_audioOutputDevice;}
    void startRecordAndPlayBack();
    void stopRecordAndPlayback();
};

#endif // NESPAUDIO_H
