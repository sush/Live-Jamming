#ifndef NESPAUDIO_H
#define NESPAUDIO_H
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioFormat>
#include <qdebug.h>
#include <QTimer>
#include <QBuffer>
#include <QFile>

class NespAudio : public QObject
{
    Q_OBJECT;
public:
    NespAudio();
    QStringList getIDevices();
    QStringList getODevices();
    void startIO();
    void stopIO();
    QAudioDeviceInfo iDevice;
    QAudioDeviceInfo oDevice;
public slots:
    void stopRecording();
    void finishedPlaying(QAudio::State);
    void stateChanged(QAudio::State);
signals:
private:
    QStringList getDevices(QAudio::Mode);
    QIODevice* inputBuffer;
    QFile inputFile;
    QAudioInput* input;
    QAudioOutput* output;
};

#endif // NESPAUDIO_H
