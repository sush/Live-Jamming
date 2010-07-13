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

//#include <Protocol_Session.h>

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
    qRegisterMetaType<chanEventsType>("MainWindow::chanEventsType");

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
        //ui->statusBar->clearMessage();
        //ui->statusBar->addWidget(new QLabel(connected ? "Connected" : "Disconnected"));
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
        params.clearId();
        break ;
    case DUPPLICATE:
        QMessageBox::critical(this, "Authentication error", "Already logged in");
        params.clearId();
        break ;
    }
}

void    MainWindow::chanEvents(chanEventsType event, const Packet_v1_Channel* packet)
{
    switch(event) {
    case JOIN_OK:
        qDebug() << "JOIN_OK" << packet->getChannelId() << ":" << packet->getChannelName();
        proxy->trans[packet->getChannelName()] = packet->getChannelId();
        joinChannel(packet->getChannelName());
        break;
    case LEAVE_OK:
        qDebug() << "LEAVE_OK" << packet->getChannelName();
        proxy->trans.remove(packet->getChannelName());
        leaveChannel(packet->getChannelName());
        break;
    case JOINED:
        qDebug() << packet->getClientLogin() << "HAS JOINED" << proxy->channel()->getAllChannel().size();
        addClientToChannel(packet->getChannelName(), packet->getClientLogin());
        break;
    case LEAVED:
        qDebug() << packet->getClientLogin() << "HAS LEAVED" << proxy->channel()->getAllChannel().size();
        removeClientFromChannel(packet->getChannelName(), packet->getClientLogin());
        break;
    case MESSAGE_RECV:
        qDebug() << "MESSAGE_RECV" << packet->getMessage();
        break;
    }
}

void    MainWindow::joinChannel(const QString &name)
{
    QTreeWidgetItem* top = new QTreeWidgetItem(QStringList(name));
    ui->channelList->addTopLevelItem(top);

    channels[name] = (UiChannel){top, 0};
}

void    MainWindow::leaveChannel(const QString &name)
{
    qDebug() << "leaving" << name;
    delete channels[name].item;
}

void    MainWindow::addClientToChannel(const QString &channel, const QString &login)
{
    qDebug() << login << "HAS JOIN" << channel;
    QMap<QString, UiChannel>::const_iterator it = channels.find(channel);
    Q_ASSERT(it != channels.end());

    QTreeWidgetItem* client = new QTreeWidgetItem(QStringList(login));
    it->item->addChild(client);
    clients[login] = (UiClient){client};
}

void    MainWindow::removeClientFromChannel(const QString &channel, const QString &login)
{
    qDebug() << login << "HAS LEAVED" << channel;
    QMap<QString, UiChannel>::const_iterator it = channels.find(channel);
    Q_ASSERT(it != channels.end());

    it->item->removeChild(clients[login].item);
    clients.remove(login);
}

void MainWindow::on_actionConnect_triggered()
{
    if (isConnected == false) {
           AccountConnection::run(params.login, params.password);

           if (params.haveId() == true) {
            qDebug() << params.login << params.password;
            proxy->session()->Connect(params.login.toStdString(), params.password.toStdString());
        }
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

void MainWindow::on_channelList_customContextMenuRequested(QPoint pos)
{
    if (ui->channelList->indexAt(pos).isValid()) {
        QTreeWidgetItem* item = ui->channelList->itemAt(pos);
        QAction leave(QString("leave"), 0);
        QAction* action = QMenu::exec(QList<QAction*>() << &leave, ui->channelList->mapToGlobal(pos));
        qDebug() << "SEDING LEAVE ON:" << proxy->trans[item->text(0)];
        if (action == &leave)
            proxy->channel()->Send_Leave(proxy->session()->_session, proxy->trans[item->text(0)]);
    }
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString currentChannel = ui->channelList->currentItem()->text(0);
    qDebug() << "WRITING ON" << currentChannel;
    proxy->channel()->Send_Message(proxy->session()->_session, ui->lineEdit->text().toLocal8Bit().data(), proxy->trans[currentChannel]);
}

void MainWindow::on_channelList_activated(const QModelIndex& index)
{

}
