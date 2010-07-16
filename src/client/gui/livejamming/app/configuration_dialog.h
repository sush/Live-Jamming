#ifndef CONFIGURATION_DIALOG_H
#define CONFIGURATION_DIALOG_H

#include <QDialog>
#include "nespaudio.h"
#include "qdebug.h"

namespace Ui {
    class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
Q_OBJECT
public:
    ConfigurationDialog(QWidget *parent = 0);

private:
    Ui::ConfigurationDialog*	ui;
    NespAudio                   audio;

private slots:
    void on_pushButton_clicked(bool);
};

#endif // CONFIGURATION_DIALOG_H
