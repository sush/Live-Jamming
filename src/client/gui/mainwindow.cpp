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

#include "boost/asio.hpp"
#include "boost/threadpool.hpp"
#include <Protocol_Session.h>

#include <Component_Session.h>
#include <Component_Channel.h>
#include <Session.h>
#include <Packet_v1.h>

#include <QDebug>

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
    setVisible(true);
    showMaximized();

    QPalette pal = palette();
    pal.setColor(backgroundRole(), Qt::black);
    setPalette(pal);
    setStyleSheet("QMainWindow { background-color: black; } QToolBar {background-color: black; }");

    setConnected(false);

    connect(this, SIGNAL(sConnectionAnswer(bool)), this, SLOT(connectionAnswer(bool)), Qt::QueuedConnection);
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

void MainWindow::setConnected(bool state)
{
    if (state != isConnected) {
        isConnected = state;
        ui->statusBar->showMessage(state ? "Connected" : "Disconnected");
        ui->menuFile->removeAction(state ? ui->actionConnect : ui->actionDisconnect);
        ui->menuFile->insertAction(ui->actionCreate_account,
                               state ? ui->actionDisconnect : ui->actionConnect);
        _channel = new Component_Channel(this);
        const Component_Channel::m_channel& list = _channel->getAllChannel();

        ui->ChansList->insertTopLevelItems(1, QList<QTreeWidgetItem*>());
        Component_Channel::m_channel::const_iterator it, end = list.end();
        for (it = list.begin(); it != end; ++it)
            ui->ChansList->insertTopLevelItem(0, new QTreeWidgetItem(ui->ChansList, QStringList(QString::number(it->first))));


    }

    if (state) { // tricks for populating lists since the server is unfinished for now
        //populate_chans();
        //populate_friends();
    }
}

void MainWindow::connectionAnswer(bool success)
{
    if (success == true)
        setConnected(true);
    else
        QMessageBox::critical(this, "Server Error", "Unable to connect to server");

}

void    MainWindow::authresponse_ok(const Packet_v1 *packet_v1, Session *session)
{
    emit sConnectionAnswer(true);
}

void MainWindow::authresponse_nok_badauth(const Packet_v1 *, Session *)
{
    emit sConnectionAnswer(false);
}


void MainWindow::on_actionConnect_triggered()
{
    if (isConnected)
        return ;

    if (params.haveId() == false)
       AccountConnection::run(params.login, params.password);

    if (params.haveId() == true) // n'est pas le contraire de la ligne au dessus.
        _session->Connect(params.login.toStdString(), params.password.toStdString());
}

void MainWindow::on_actionDisconnect_triggered()
{
    _session->Disconnect();
    setConnected(false);
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

    static int id = 0;
    _channel->Send_Join(_session->_session, id);
    dialui.nameLineEdit->setText(QString::number(id));
    dial.exec();
    if (!dialui.nameLineEdit->text().isEmpty()) {
        //ui->ChansList->addTopLevelItem(new QTreeWidgetItem(QStringList() << dialui.nameLineEdit->text() << dialui.subjectLabel->text()));
        ui->ChansList->addTopLevelItem(new QTreeWidgetItem(QStringList() << dialui.nameLineEdit->text()));
        _channel->Send_Join(_session->_session, dialui.nameLineEdit->text().toLong());

     id++;
    }
}

void MainWindow::add_chan(const QString &name)
{
    convSet*    convset = new convSet(ui->convsTab);
    ui->convsTab->addTab(convset, name);
}

void MainWindow::on_ChansList_itemActivated(QTreeWidgetItem* item, int column)
{

}
