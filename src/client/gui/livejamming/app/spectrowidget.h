#ifndef SPECTROWIDGET_H
#define SPECTROWIDGET_H

#include <QWidget>
#include <QAudioFormat>
#include <QtMultimedia/qaudio.h>

class NespAudio;
class FrequencySpectrum;
class Spectrograph;

class SpectroWidget : public QWidget
{
Q_OBJECT
public:
    SpectroWidget(QWidget *parent = 0, NespAudio *m_engine = 0);
    ~SpectroWidget();

//signals:
//    void infoMessage(const QString &message, int timeoutMs);
//    void errorMessage(const QString &heading, const QString &detail);
//    void positionChanged(qint64 position);

public slots:
    void stateChanged(QAudio::Mode mode, QAudio::State state);
 //   void formatChanged(const QAudioFormat &format);
    void spectrumChanged(qint64 position, qint64 length,
                         const FrequencySpectrum &spectrum);
    void bufferDurationChanged(qint64 duration);
private:
    void createUi();
    void reset();
private:
    NespAudio* m_engine;
    Spectrograph* m_spectrograph;
};

#endif // SPECTROWIDGET_H
