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
#include <QDebug>

#include "accountconnection.h"
#include "configuration_dialog.h"
#include "roomdialog.h"

#include <Component_Session.h>
#include <Component_Channel.h>
#include <Session.h>
#include <Packet_v1.h>
#include <Client.h>
#include <proxy.h>
#include <conversationset.h>



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
    /* Set apllication indentity*/
    QCoreApplication::setOrganizationName("LiveJamming");
    QCoreApplication::setOrganizationDomain("live-jamming.com");
    QCoreApplication::setApplicationName("Live Jamming");
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
        ui->menuChans->setEnabled(connected);
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
        setConnected(false);
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
        proxy->channelNameToId[packet->getChannelName()] = packet->getChannelId();
        joinChannel(packet->getChannelName());
        break;
    case LEAVE_OK:
        proxy->channelNameToId.remove(packet->getChannelName());
        leaveChannel(packet->getChannelName());
        break;
    case JOINED:

        addClientToChannel(packet->getChannelName(), packet->getClientLogin());
        break;
    case LEAVED:
        removeClientFromChannel(packet->getChannelName(), packet->getClientLogin());
        break;
    case MESSAGE_RECV:
        addMessage(proxy->channelIdToName(packet->getChannelId()), "toto", packet->getMessage());
        break;
    }
}

void    MainWindow::joinChannel(const QString &name)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(name));
    ui->channelList->addTopLevelItem(item);

    ConversationSet* convSet = new ConversationSet;
    connect(convSet->input, SIGNAL(returnPressed()), this, SLOT(on_lineEdit_returnPressed()));
    ui->stackedWidget->addWidget(convSet);
    ui->stackedWidget->setCurrentWidget(convSet);
    currentChannel = name;

    channels[name] = (UiChannel){item, convSet};
    addClientToChannel(name, settings.value("user/login").toString());
}

void    MainWindow::leaveChannel(const QString &name)
{
    delete channels[name].item;

    channels.remove(name);
}

void    MainWindow::addClientToChannel(const QString &channel, const QString &client)
{
//    QMap<QString, UiChannel>::const_iterator it = channels.find(channel);
//    Q_ASSERT(it != channels.end());

    Q_ASSERT(channels.find(channel) != channels.end());
    QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(client));
    channels[channel].item->addChild(item);

    clients[client] = (UiClient){item};
}

void    MainWindow::removeClientFromChannel(const QString &channel, const QString &client)
{
//    QMap<QString, UiChannel>::const_iterator it = channels.find(channel);
//    Q_ASSERT(it != channels.end());
qDebug() << channel << client << channels.size();
    Q_ASSERT(channels.find(channel) != channels.end());
    Q_ASSERT(clients.find(client) != clients.end());
    delete clients[client].item;

    clients.remove(client);
}

void    MainWindow::addMessage(const QString &channel, const QString &client, const QString &msg)
{
    Q_ASSERT(channels.contains(channel));
    //Q_ASSERT(clients.contains(client));

    ConversationSet* convSet = static_cast<ConversationSet*>(ui->stackedWidget->currentWidget());
    convSet->display->setPlainText(convSet->display->toPlainText() + "\n" + client + ": " + msg);
}

void MainWindow::on_actionConnect_triggered()
{
    if (isConnected == false) {
           if (AccountConnection::run(this,
                                   settings.value("user/login", "dude").toString(),
                                   settings.value("user/password", "12345678").toString(),
                                   settings.value("server/ip", "127.0.0.1").toString(),
                                   settings.value("server/port", "5042").toString()
                                   )) {
           if (settings.contains("user/login") == true) {
               proxy->client->Connect(
                       settings.value("server/ip").toString().toStdString(),
                       settings.value("server/port").toInt());
            proxy->session()->Connect(
                    settings.value("user/login").toString().toStdString(),
                    settings.value("user/password").toString().toStdString());
        }
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
qDebug() << "toto" << ui->channelList->itemAt(pos)->text(0);
        if (channels.contains(item->text(0))) {
            QAction leave(QString("leave"), 0);
            QAction* action = QMenu::exec(QList<QAction*>() << &leave, ui->channelList->mapToGlobal(pos));
            qDebug() << "SEDING LEAVE ON:" << proxy->channelNameToId[item->text(0)];
            if (action == &leave)
                proxy->channel()->Send_Leave(proxy->session()->_session, proxy->channelNameToId[item->text(0)]);
        }
    }
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString msg = channels.value(currentChannel).convSet->input->text();
    qDebug() << "SENDING MSG" << msg << "FROM" << currentChannel;

    proxy->channel()->Send_Message(proxy->session()->_session, msg.toLocal8Bit().data(), proxy->channelNameToId[currentChannel]);
    channels.value(currentChannel).convSet->input->clear();
}

void MainWindow::on_channelList_activated(const QModelIndex& index)
{
    currentChannel = ui->channelList->itemFromIndex(index)->text(0);
    ui->stackedWidget->setCurrentWidget(channels[currentChannel].convSet);
}
