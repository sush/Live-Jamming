#include "audiosettingswidget.h"
#include "ui_audiosettingswidget.h"

AudioSettingsWidget::AudioSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioSettingsWidget)
{
    ui->setupUi(this);
}

AudioSettingsWidget::~AudioSettingsWidget()
{
    delete ui;
}

void AudioSettingsWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
