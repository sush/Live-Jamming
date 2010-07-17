#ifndef AUDIOWIDGET_H
#define AUDIOWIDGET_H

#include <QWidget>
#include <QtMultimedia/qaudio.h>

class AudioEngine;
class FrequencySpectrum;
class ProgressBar;
class Spectrograph;
class Waveform;
class LevelMeter;
class SettingsDialog;
class ToneGeneratorDialog;

QT_FORWARD_DECLARE_CLASS(QAudioFormat)
QT_FORWARD_DECLARE_CLASS(QLabel)

class AudioWidget : public QWidget
{
    Q_OBJECT
public:
    AudioWidget(QWidget *parent = 0);
    ~AudioWidget();

    // QObject
    void                    timerEvent(QTimerEvent *event);

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

#endif // AUDIOWIDGET_H
