#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QUrl>
#include <QTreeWidgetItem>

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
    params = new Parameters();

    QTreeWidgetItem* root = new QTreeWidgetItem(ui->ChanList);
    root->setText(0,"General");
    QTreeWidgetItem* custom = new QTreeWidgetItem(ui->ChanList);
    custom->setText(0, "Custom");

    ui->ChanList->insertTopLevelItems(1, QList<QTreeWidgetItem*>()
                                        << new QTreeWidgetItem(custom, QStringList("Rock"))
                                        << new QTreeWidgetItem(custom, QStringList("Metal")));
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

    if (params->haveId() == false)
       AccountConnection::run(params->login, params->password);

    if (params->haveId() == true) // n'est pas le contraire de la ligne au dessus.
        network->connect(params->login, params->password);
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

void MainWindow::on_actionCreate_account_triggered()
{
    QDesktopServices::openUrl(QUrl("http://live-jamming.com/users/register"));
}
