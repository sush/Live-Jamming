#include "ui_configuration_dialog.h"
#include "configuration_dialog.h"
#include <qdebug.h>


ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    // AudioEngine* audioEngine = new AudioEngine();

    // ui->setupUi(this);

    // /*Setting ui for input*/
    // ui->iComboBox->addItems(audioEngine->inputDevices());
    // foreach (int channel, audioEngine->inputDevice().supportedChannels())
    //     ui->iChannelsComboBox->addItem(QString::number(channel));
    // ui->iCodecsComboBox->addItems(audioEngine->inputDevice().supportedCodecs());
    // foreach (int frequency, audioEngine->inputDevice().supportedFrequencies())
    //     ui->iFrequenciesComboBox->addItem(QString::number(frequency));
    // foreach (int sampleSize, audioEngine->inputDevice().supportedSampleSizes())
    //     ui->iSampleSizesComboBox->addItem(QString::number(sampleSize));
    /*Setting ui for output*/
//    ui->oComboBox->addItems(audioEngine->outputDevices());
//    foreach (int channel, audioEngine->outputDevice().supportedChannels())
//        ui->oChannelsComboBox->addItem(QString::number(channel));
//    ui->oCodecsComboBox->addItems(audioEngine->outputDevice().supportedCodecs());
//    foreach (int frequency, audioEngine->outputDevice().supportedFrequencies())
//        ui->oFrequenciesComboBox->addItem(QString::number(frequency));
//    foreach (int sampleSize, audioEngine->outputDevice().supportedSampleSizes())
//        ui->oSampleSizesComboBox->addItem(QString::number(sampleSize));
}

ConfigurationDialog::~ConfigurationDialog(){
}


