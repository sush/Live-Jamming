#ifndef CONFIGURATION_DIALOG_H
#define CONFIGURATION_DIALOG_H
#include "qdebug.h"

#include <QDialog>


namespace Ui {
    class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
Q_OBJECT
public:
    ConfigurationDialog(QWidget *parent = 0);
    ~ConfigurationDialog();

private:
    Ui::ConfigurationDialog*	ui;
private slots:
    //void on_pushButton_clicked(bool);
};

#endif // CONFIGURATION_DIALOG_H
