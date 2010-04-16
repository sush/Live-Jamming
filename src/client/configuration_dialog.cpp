#include "ui_configuration_dialog.h"
#include "configuration_dialog.h"
#include <qdebug.h>
ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
  ui->setupUi(this);
  ui->comboBox->addItem(QString("plop"), QVariant(0));
}

void ConfigurationDialog::on_buttonBox_accepted()
{
    qDebug() << ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt();
}
