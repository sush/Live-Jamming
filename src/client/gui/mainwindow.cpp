#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_newchan.h"

#include <QDesktopServices>
#include <QUrl>
#include <QTreeWidgetItem>
#include <QInputDialog>
#include <QString>
#include <QModelIndex>

#include "parameters.h"
#include "accountconnection.h"
#include "configuration_dialog.h"
#include "roomdialog.h"
#include "convset.h"

#include "boost/asio.hpp"
#include "boost/threadpool.hpp"

#include <Component_Session.h>
#include <Session.h>
#include <Packet_v1.h>

void    MainWindow::populate_chans()
{
    /*QTreeWidgetItem* root =*/ new QTreeWidgetItem(ui->ChansList, QStringList() << "General" << "The General Chan");
    QTreeWidgetItem* custom = new QTreeWidgetItem(ui->ChansList, QStringList() << "Custom" << "Custom created Chans");

    ui->ChansList->insertTopLevelItems(1, QList<QTreeWidgetItem*>()
                                        << new QTreeWidgetItem(custom, QStringList("Rock") << "Rock the world")
                                        << new QTreeWidgetItem(custom, QStringList("Metal") << "Damn the earth"));
}

void    MainWindow::populate_friends()
{
    ui->FriendsList->insertTopLevelItems(0, QList<QTreeWidgetItem*>()
                                      << new QTreeWidgetItem(QStringList("Pierre"))
                                      << new QTreeWidgetItem(QStringList("Aylyc"))
                                      << new QTreeWidgetItem(QStringList("Sush"))
                                      << new QTreeWidgetItem(QStringList("Greg")));
}

MainWindow::MainWindow(boost::asio::io_service& service, boost::threadpool::pool& pool,
                       boost::asio::ip::udp::socket& socket, boost::asio::ip::udp::endpoint& endpoint) :
    QMainWindow(0),
    ClientManager(service, pool, socket, endpoint),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    params = new Parameters();

    populate_chans();
    populate_friends();
}

MainWindow::~MainWindow()

{
    delete ui;
}

int MainWindow::gui_init(int argc, char* argv[])
{
    QApplication a(argc, argv);
}

void    MainWindow::run()
{
return a.exec();
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
    if (isConnected)
        return ;

    if (params->haveId() == false)
       AccountConnection::run(params->login, params->password);

    if (params->haveId() == true) // n'est pas le contraire de la ligne au dessus.
        _session->Connect(params->login.toStdString(), params->password.toStdString());
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

void MainWindow::on_actionAdd_Friend_triggered()
{
    QString friendName = QInputDialog::getText(this, tr("Add a friend"), tr("friend's name"));
    if (!friendName.isEmpty())
        ui->FriendsList->addTopLevelItem(new QTreeWidgetItem(QStringList(friendName)));
}

void MainWindow::on_actionNew_Chan_triggered()
{
    Ui::NewChan dialui;
    QDialog dial;
    dialui.setupUi(&dial);

    dial.exec();
    if (!dialui.nameLineEdit->text().isEmpty())
        ui->ChansList->addTopLevelItem(new QTreeWidgetItem(QStringList() << dialui.nameLineEdit->text() << dialui.subjectLabel->text()));
}

void    MainWindow::auth_session_ok(const Packet_v1 *, Session *)
{
    connected();
}

void MainWindow::on_ChansList_activated(QModelIndex &index)
{

}

void MainWindow::add_chan(const QString &name)
{
    convSet*    convset = new convSet(ui->convsTab);
    ui->convsTab->addTab(convset, name);
}
