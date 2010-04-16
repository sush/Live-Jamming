#ifndef CONFIGURATION_DIALOG_H
#define CONFIGURATION_DIALOG_H

#include <QDialog>

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


private slots:
    void on_buttonBox_accepted();
};

#endif // CONFIGURATION_DIALOG_H
