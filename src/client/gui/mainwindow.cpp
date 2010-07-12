#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_newchan.h"

#include <QDesktopServices>
#include <QUrl>
#include <QTreeWidgetItem>
#include <QInputDialog>
#include <QString>
#include <QModelIndex>
#include <QTimer>
#include <QMessageBox>
#include <QThread>

#include "parameters.h"
#include "accountconnection.h"
#include "configuration_dialog.h"
#include "roomdialog.h"
#include "convset.h"

//#include "boost/asio.hpp"
//#include "boost/threadpool.hpp"
#include <Protocol_Session.h>

#include <Component_Session.h>
#include <Component_Channel.h>
#include <Session.h>
#include <Packet_v1.h>
#include <proxy.h>

#include <QDebug>

MainWindow::MainWindow() :
    QMainWindow(),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setVisible(true);
    qRegisterMetaType<authEventsType>("MainWindow::authEventsType");

    setConnected(false);
    connect(QCoreApplication::instance(), SIGNAL(aboutToQuit()), this, SLOT(on_actionDisconnect_triggered()));

    QTimer::singleShot(0, this, SLOT(on_actionConnect_triggered()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::gui_init(int argc, char* argv[])
{
    new QApplication(argc, argv);
}

int    MainWindow::run()
{
    return QApplication::exec();
}

void   MainWindow::setProxy(Proxy *proxy_)
{
    proxy = proxy_;
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

void MainWindow::setConnected(bool connected)
{
    if (connected != isConnected) {
        isConnected = connected;
        ui->statusBar->showMessage(connected ? "Connected" : "Disconnected");
        ui->menuFile->removeAction(connected ? ui->actionConnect : ui->actionDisconnect);
        ui->menuFile->insertAction(ui->actionCreate_account,
                                   connected ? ui->actionDisconnect : ui->actionConnect);
        ui->textEdit->setEnabled(connected);
    }

}

void MainWindow::authEvents(authEventsType event)
{
    switch (event) {
    case OK:
        setConnected(true);
        break;
    case DISCONNECTED:
        QMessageBox::critical(this, "Connection Error", "You've been disconnected");
        setConnected(false);
        break;
    case BADAUTH:
        QMessageBox::critical(this, "Authentication error", "Wrong login/password");
        break ;
    case DUPPLICATE:
        QMessageBox::critical(this, "Authentication error", "Already logged in");
        break ;
    }
}

void    MainWindow::chanEvents(chanEventsType event, const Packet_v1_Channel* packet)
{
    switch(event) {
        case JOIN_OK:
            qDebug() << packet->getChannelName();
        break;

    }
}

void    MainWindow::chanJoinOk(const char *)
{

}

void MainWindow::on_actionConnect_triggered()
{
    if (isConnected == false) {
        if (params.haveId() == false)
           AccountConnection::run(params.login, params.password);

        if (params.haveId() == true) // n'est pas le contraire de la ligne au dessus.
            proxy->session()->Connect(params.login.toStdString(), params.password.toStdString());
    }
}

void MainWindow::on_actionDisconnect_triggered()
{
    if (isConnected == true) {
        proxy->session()->Disconnect();
        setConnected(false);
    }
}

void MainWindow::on_actionPreferences_triggered()
{
    ConfigurationDialog().exec();
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCreate_account_triggered()
{
    QDesktopServices::openUrl(QUrl("http://live-jamming.com/users/register"));
}

void MainWindow::on_actionAdd_Friend_triggered()
{
    QString friendName = QInputDialog::getText(this, tr("Add a friend"), tr("friend's name"));
//    if (!friendName.isEmpty())
//        ui->friendsList->addTopLevelItem(new QTreeWidgetItem(QStringList(friendName)));
}

void MainWindow::on_actionCreate_Channel_triggered()
{
    Ui::NewChan dialui;
    QDialog dial;
    dialui.setupUi(&dial);

    dial.exec();
    if ( !dialui.nameLineEdit->text().isEmpty()) {
        proxy->channel()->Send_Join(proxy->session()->_session, dialui.nameLineEdit->text().toLocal8Bit().data());
    }
}
