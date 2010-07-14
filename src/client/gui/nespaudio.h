#ifndef NESPAUDIO_H
#define NESPAUDIO_H
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioFormat>
#include <qdebug.h>

class NespAudio
{
public:
    NespAudio();
    QStringList getIDevices();
    QStringList getODevices();
    QString getDefaultODevice();
    QString getDefaultIDevice();
    void testAudio();
private:
    QStringList getDevices(QAudio::Mode);

};

#endif // NESPAUDIO_H
