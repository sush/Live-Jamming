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
    QString getDefaultODevice();
    QString getDefaultIDevice();
    void startIO();
    void stopIO();
public slots:
    void stopRecording();
    void finishedPlaying(QAudio::State);
    void stateChanged(QAudio::State);
signals:
private:
    QStringList getDevices(QAudio::Mode);
    QAudioInput* input;
    QAudioOutput* output;
    QIODevice* inputBuffer;
    QFile inputFile;
};

#endif // NESPAUDIO_H