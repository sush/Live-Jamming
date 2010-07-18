#include "audiomanager.h"
#include "audioengine.h"
#include "levelmeter.h"
#include "waveform.h"
#include "progressbar.h"
#include "settingsdialog.h"
#include "spectrograph.h"
#include "tonegeneratordialog.h"
#include "utils.h"

#include <QTimerEvent>
#include <QMessageBox>

const int NullTimerId = -1;

AudioManager::AudioManager(QWidget *parent)
    :   QWidget(parent), m_engine(new AudioEngine())
//    ,   m_engine(new AudioEngine())
//#ifndef DISABLE_WAVEFORM
//    ,   m_waveform(new Waveform(m_engine->buffer(), this))
//#endif
//    ,   m_progressBar(new ProgressBar(this))
//    ,   m_spectrograph(new Spectrograph(this))
//    ,   m_levelMeter(new LevelMeter(this))
//    ,   m_infoMessageTimerId(NullTimerId)
{
    //m_spectrograph->setParams(SpectrumNumBands, SpectrumLowFreq, SpectrumHighFreq);
}

AudioManager::~AudioManager(){}

//-----------------------------------------------------------------------------
// Public functions
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Public slots
//-----------------------------------------------------------------------------
void AudioManager::stateChanged(QAudio::Mode mode, QAudio::State state)
{
    Q_UNUSED(mode);

    //updateButtonStates();

    if (QAudio::ActiveState != state && QAudio::SuspendedState != state) {
        m_levelMeter->reset();
        m_spectrograph->reset();
    }
}

void AudioManager::formatChanged(const QAudioFormat &format)
{
   infoMessage(formatToString(format), NullMessageTimeout);

#ifndef DISABLE_WAVEFORM
    if (QAudioFormat() != format) {
        m_waveform->initialize(format, WaveformTileLength,
                               WaveformWindowDuration);
    }
#endif
}

void AudioManager::spectrumChanged(qint64 position, qint64 length,
                                 const FrequencySpectrum &spectrum)
{
    m_progressBar->windowChanged(position, length);
    m_spectrograph->spectrumChanged(spectrum);
}

void AudioManager::infoMessage(const QString &message, int timeoutMs)
{
    //m_infoMessage->setText(message);

    if (NullTimerId != m_infoMessageTimerId) {
        killTimer(m_infoMessageTimerId);
        m_infoMessageTimerId = NullTimerId;
    }

    if (NullMessageTimeout != timeoutMs)
        m_infoMessageTimerId = startTimer(timeoutMs);
}

void AudioManager::errorMessage(const QString &heading, const QString &detail)
{
    QMessageBox::warning(this, heading, detail, QMessageBox::Close);
}

void AudioManager::timerEvent(QTimerEvent *event)
{
    Q_ASSERT(event->timerId() == m_infoMessageTimerId);
    Q_UNUSED(event) // suppress warnings in release builds
    killTimer(m_infoMessageTimerId);
    m_infoMessageTimerId = NullTimerId;
    //m_infoMessage->setText("");
}

void AudioManager::positionChanged(qint64 positionUs)
{
#ifndef DISABLE_WAVEFORM
    qint64 positionBytes = audioLength(m_engine->format(), positionUs);
    m_waveform->positionChanged(positionBytes);
#else
    Q_UNUSED(positionUs)
#endif
}

void AudioManager::bufferDurationChanged(qint64 durationUs)
{
    m_progressBar->bufferDurationChanged(durationUs);
}


//-----------------------------------------------------------------------------
// Private slots
//-----------------------------------------------------------------------------

void AudioManager::dataDurationChanged(qint64 duration)
{
#ifndef DISABLE_WAVEFORM
    const qint64 dataLength = audioLength(m_engine->format(), duration);
    m_waveform->dataLengthChanged(dataLength);
#else
    Q_UNUSED(duration)
#endif

    //updateButtonStates();
}

//void MainWidget::showSettingsDialog()
//{
//    reset();
//    m_settingsDialog->exec();
//    if (m_settingsDialog->result() == QDialog::Accepted) {
//        m_engine->setAudioInputDevice(m_settingsDialog->inputDevice());
//        m_engine->setAudioOutputDevice(m_settingsDialog->outputDevice());
//        m_engine->setWindowFunction(m_settingsDialog->windowFunction());
//    }
//}


//void MainWidget::initializeRecord()
//{
//    reset();
//    setMode(RecordMode);
//    if (m_engine->initializeRecord())
//       updateButtonStates();
//}


//-----------------------------------------------------------------------------
// Private functions
//-----------------------------------------------------------------------------

//void MainWidget::connectUi()
//{
//    CHECKED_CONNECT(m_recordButton, SIGNAL(clicked()),
//            m_engine, SLOT(startRecording()));
//
//    CHECKED_CONNECT(m_pauseButton, SIGNAL(clicked()),
//            m_engine, SLOT(suspend()));
//
//    CHECKED_CONNECT(m_playButton, SIGNAL(clicked()),
//            m_engine, SLOT(startPlayback()));
//
//    CHECKED_CONNECT(m_settingsButton, SIGNAL(clicked()),
//            this, SLOT(showSettingsDialog()));
//
//    CHECKED_CONNECT(m_engine, SIGNAL(stateChanged(QAudio::Mode,QAudio::State)),
//            this, SLOT(stateChanged(QAudio::Mode,QAudio::State)));
//
//    CHECKED_CONNECT(m_engine, SIGNAL(formatChanged(const QAudioFormat &)),
//            this, SLOT(formatChanged(const QAudioFormat &)));
//
//    m_progressBar->bufferDurationChanged(m_engine->bufferDuration());
//
//    CHECKED_CONNECT(m_engine, SIGNAL(bufferDurationChanged(qint64)),
//            this, SLOT(bufferDurationChanged(qint64)));
//
//    CHECKED_CONNECT(m_engine, SIGNAL(dataDurationChanged(qint64)),
//            this, SLOT(dataDurationChanged(qint64)));
//
//    CHECKED_CONNECT(m_engine, SIGNAL(recordPositionChanged(qint64)),
//            m_progressBar, SLOT(recordPositionChanged(qint64)));
//
//    CHECKED_CONNECT(m_engine, SIGNAL(playPositionChanged(qint64)),
//            m_progressBar, SLOT(playPositionChanged(qint64)));
//
//    CHECKED_CONNECT(m_engine, SIGNAL(recordPositionChanged(qint64)),
//            this, SLOT(positionChanged(qint64)));
//
//    CHECKED_CONNECT(m_engine, SIGNAL(playPositionChanged(qint64)),
//            this, SLOT(positionChanged(qint64)));
//
//    CHECKED_CONNECT(m_engine, SIGNAL(levelChanged(qreal, qreal, int)),
//            m_levelMeter, SLOT(levelChanged(qreal, qreal, int)));
//
//    CHECKED_CONNECT(m_engine, SIGNAL(spectrumChanged(qint64, qint64, const FrequencySpectrum &)),
//            this, SLOT(spectrumChanged(qint64, qint64, const FrequencySpectrum &)));
//
//    CHECKED_CONNECT(m_engine, SIGNAL(infoMessage(QString, int)),
//            this, SLOT(infoMessage(QString, int)));
//
//    CHECKED_CONNECT(m_engine, SIGNAL(errorMessage(QString, QString)),
//            this, SLOT(errorMessage(QString, QString)));
//
//    CHECKED_CONNECT(m_spectrograph, SIGNAL(infoMessage(QString, int)),
//            this, SLOT(infoMessage(QString, int)));
//}

//void MainWidget::createMenus()
//{
//    m_modeButton->setMenu(m_modeMenu);
//
//    m_generateToneAction = m_modeMenu->addAction(tr("Play generated tone"));
//    m_recordAction = m_modeMenu->addAction(tr("Record and play back"));
//    m_loadFileAction = m_modeMenu->addAction(tr("Play file"));
//
//    m_loadFileAction->setCheckable(true);
//    m_generateToneAction->setCheckable(true);
//    m_recordAction->setCheckable(true);
//
//    connect(m_loadFileAction, SIGNAL(triggered(bool)), this, SLOT(showFileDialog()));
//    connect(m_generateToneAction, SIGNAL(triggered(bool)), this, SLOT(showToneGeneratorDialog()));
//    connect(m_recordAction, SIGNAL(triggered(bool)), this, SLOT(initializeRecord()));
//}

void AudioManager::reset()
{
#ifndef DISABLE_WAVEFORM
    m_waveform->reset();
#endif
    m_engine->reset();
    m_levelMeter->reset();
    m_spectrograph->reset();
    m_progressBar->reset();
}

/*void MainWidget::setMode(Mode mode)
{

    m_mode = mode;
    m_loadFileAction->setChecked(LoadFileMode == mode);
    m_generateToneAction->setChecked(GenerateToneMode == mode);
    m_recordAction->setChecked(RecordMode == mode);
}
*/
