#include "spectrowidget.h"
#include "nespaudio.h"
#include "spectrograph.h"
#include "utils.h"

#include <QVBoxLayout>

SpectroWidget::SpectroWidget(QWidget *parent, NespAudio *m_engine) :
    QWidget(parent),  m_engine(m_engine), m_spectrograph(new Spectrograph(this))
{

}

SpectroWidget::~SpectroWidget(){
}

//-----------------------------------------------------------------------------
// Public slots
//-----------------------------------------------------------------------------

void SpectroWidget::stateChanged(QAudio::Mode mode, QAudio::State state)
{
    Q_UNUSED(mode);

    if (QAudio::ActiveState != state && QAudio::SuspendedState != state) {
        m_spectrograph->reset();
    }
}

void SpectroWidget::spectrumChanged(qint64 position, qint64 length,
                                 const FrequencySpectrum &spectrum)
{
  m_spectrograph->spectrumChanged(spectrum);
}

void SpectroWidget::bufferDurationChanged(qint64 durationUs)
{
    //m_progressBar->bufferDurationChanged(durationUs);
}

void SpectroWidget::createUi(){
    QVBoxLayout *windowLayout = new QVBoxLayout(this);
    QScopedPointer<QHBoxLayout> analysisLayout(new QHBoxLayout);

    analysisLayout->addWidget(m_spectrograph);
    windowLayout->addLayout(analysisLayout.data());
    analysisLayout.take();
    setLayout(windowLayout);
}

void SpectroWidget::reset(){
    m_spectrograph->reset();
}

