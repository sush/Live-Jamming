#ifndef CONFIGURATION_DIALOG_H
#define CONFIGURATION_DIALOG_H

#include <QDialog>
#ifndef NO_MULTIMEDIA
#include "nespaudio.h"
#endif
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
    #ifndef NO_MULTIMEDIA
    NespAudio                   audio;
    #endif

private slots:
    void on_pushButton_clicked(bool);
};

#endif // CONFIGURATION_DIALOG_H
