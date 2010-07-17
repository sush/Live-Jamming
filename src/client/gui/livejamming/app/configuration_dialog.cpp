#include "ui_configuration_dialog.h"
#include "configuration_dialog.h"
#ifndef NO_MULTIMEDIA
#include "spectrowidget.h"
#endif
#include <qdebug.h>
ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog),audio(new NespAudio())
{
    ui->setupUi(this);
    /*Setting ui for input*/
    #ifndef NO_MULTIMEDIA
    ui->iComboBox->addItems(audio->getIDevices());
    foreach (int channel, audio->iDevice().supportedChannels())
        ui->iChannelsComboBox->addItem(QString::number(channel));
    ui->iCodecsComboBox->addItems(audio->iDevice().supportedCodecs());
    foreach (int frequency, audio->iDevice().supportedFrequencies())
        ui->iFrequenciesComboBox->addItem(QString::number(frequency));
    foreach (int sampleSize, audio->iDevice().supportedSampleSizes())
        ui->iSampleSizesComboBox->addItem(QString::number(sampleSize));
    /*Setting ui for output*/
    ui->outputComboBox->addItems(audio->getODevices());
    foreach (int channel, audio->oDevice().supportedChannels())
        ui->oChannelsComboBox->addItem(QString::number(channel));
    ui->oCodecsComboBox->addItems(audio->oDevice().supportedCodecs());
    foreach (int frequency, audio->oDevice().supportedFrequencies())
        ui->oFrequenciesComboBox->addItem(QString::number(frequency));
    foreach (int sampleSize, audio->oDevice().supportedSampleSizes())
        ui->oSampleSizesComboBox->addItem(QString::number(sampleSize));

#endif
}

ConfigurationDialog::~ConfigurationDialog(){
    /*Verify that Engine destructor delete all Audio instances*/
    #ifndef NO_MULTIMEDIA
    delete audio;
    #endif
}

void ConfigurationDialog::on_pushButton_clicked(bool checked)
{
    if (checked){
    ui->pushButton->setText("Stop");
    #ifndef NO_MULTIMEDIA
    audio->startRecordAndPlayBack();
    #endif
}
    else {
        ui->pushButton->setText("Start");
        #ifndef NO_MULTIMEDIA
        audio->stopRecordAndPlayback();
         #endif
    }
}
