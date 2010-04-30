#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "network.h"
#include "parameters.h"
#include "accountconnection.h"
#include "configuration_dialog.h"
#include "roomdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    network = new Network();
}

MainWindow::~MainWindow()
{
    delete network;
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::connected()
{
    ui->menuBar->removeAction(ui->actionConnect);
    ui->menuBar->insertAction(NULL, ui->actionDisconnect);
}

void MainWindow::on_actionConnect_triggered()
{
    if (network->isConnected())
        return ;

    if (params->haveId())
        network->connect(params->login, params->password);
    else {
        QString login, password;
        if (AccountConnection::run(login, password) == true)
            network->connect(login, password);
    }
}

void MainWindow::on_actionPreferences_triggered()
{
    ConfigurationDialog().exec();
}

void MainWindow::on_actionNew_Room_triggered()
{
    RoomDialog().exec();
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}
