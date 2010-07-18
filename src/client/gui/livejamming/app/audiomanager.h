#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QWidget>
#include <QLabel>
#include <QtMultimedia/qaudio.h>
#include <QAudioFormat>

class AudioEngine;
class FrequencySpectrum;
class ProgressBar;
class Spectrograph;
class Waveform;
class LevelMeter;
class SettingsDialog;
class ToneGeneratorDialog;

class AudioManager : public QWidget
{
    Q_OBJECT
public:
    AudioManager(QWidget *parent = 0);
    ~AudioManager();

    // QObject
    void                    timerEvent(QTimerEvent *event);
    QStringList             getOutputDevices();
    QStringList             getInputDevices();
public slots:
    void                    stateChanged(QAudio::Mode mode, QAudio::State state);
    void                    formatChanged(const QAudioFormat &format);
    void                    spectrumChanged(qint64 position, qint64 length,
                                            const FrequencySpectrum &spectrum);
    void                    infoMessage(const QString &message, int timeoutMs);
    void                    errorMessage(const QString &heading, const QString &detail);
    void                    positionChanged(qint64 position);
    void                    bufferDurationChanged(qint64 duration);

private slots:
    void                    dataDurationChanged(qint64 duration);
private:
    void                    reset();

private:
    AudioEngine*            m_engine;
    Waveform*               m_waveform;
    ProgressBar*            m_progressBar;
    Spectrograph*           m_spectrograph;
    LevelMeter*             m_levelMeter;
    QLabel*                 m_infoMessage;
    int                     m_infoMessageTimerId;

};

#endif // AUDIOMANAGER_H
