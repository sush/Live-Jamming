#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QtMultimedia/qaudio.h>
#include <qdebug.h>

class AudioEngine : public QObject
{
    Q_OBJECT;
public:
    AudioEngine(QObject *parent = 0);


    const QStringList               inputDevices();
    const QAudioDeviceInfo&         inputDevice() const
                                    {return _inputDevice;}

private:
    bool                            initialize();
    void                            reset();
    /* INPUT */
    void                            stopRecording();
    void                            setInputState(QAudio::State);
    void                            setInputFormat(const QAudioFormat&);
    bool                            selectInputFormat();

private:


    /* INPUT */
    const QList<QAudioDeviceInfo>   _availableInputDevices;
    QAudio::State                   _inputState;
    QAudioFormat                    _inputFormat;
    QAudioDeviceInfo                _inputDevice;
    QAudioInput*                    _input;
    QIODevice*                      _inputIODevice;
    qint64                          _recordPosition;

    /* OUTPUT */
    
};

#endif // AUDIOENGINE_H
