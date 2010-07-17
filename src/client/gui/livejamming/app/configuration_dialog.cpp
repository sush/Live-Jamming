#include "ui_configuration_dialog.h"
#include "configuration_dialog.h"
#include <qdebug.h>

#ifndef NO_MULTIMEDIA
#include "audiowidget.h"

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);
    AudioWidget* audioSettings = new AudioWidget(ui->tab);
    ui->tab->layout()->addWidget(audioSettings);
    audioSettings->show();
    /*Setting ui for input*/
//    ui->iComboBox->addItems(audio->getIDevices());
//    foreach (int channel, audio->iDevice().supportedChannels())
//        ui->iChannelsComboBox->addItem(QString::number(channel));
//    ui->iCodecsComboBox->addItems(audio->iDevice().supportedCodecs());
//    foreach (int frequency, audio->iDevice().supportedFrequencies())
//        ui->iFrequenciesComboBox->addItem(QString::number(frequency));
//    foreach (int sampleSize, audio->iDevice().supportedSampleSizes())
//        ui->iSampleSizesComboBox->addItem(QString::number(sampleSize));
//    /*Setting ui for output*/
//    ui->outputComboBox->addItems(audio->getODevices());
//    foreach (int channel, audio->oDevice().supportedChannels())
//        ui->oChannelsComboBox->addItem(QString::number(channel));
//    ui->oCodecsComboBox->addItems(audio->oDevice().supportedCodecs());
//    foreach (int frequency, audio->oDevice().supportedFrequencies())
//        ui->oFrequenciesComboBox->addItem(QString::number(frequency));
//    foreach (int sampleSize, audio->oDevice().supportedSampleSizes())
//        ui->oSampleSizesComboBox->addItem(QString::number(sampleSize));
//    ui->tab->layout()->
//    ui->tab->layout()->addWidget(audio->getSpectrograph());
    //this->layout()->addWidget(audio->getSpectrograph());
}

#elif defined(NO_MULTIMEDIA)
ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{

}
#endif

ConfigurationDialog::~ConfigurationDialog(){
}

//void ConfigurationDialog::on_pushButton_clicked(bool checked)
//{
//    if (checked){
//}
//    else {
//        ui->pushButton->setText("Start");
//    }
//}
