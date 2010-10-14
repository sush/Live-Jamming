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
#include <proxy.h>
#include <conversationset.h>
#include <channelsearch.h>

#include <Component_Session.h>
#include <Component_Channel.h>
#include <Component_Room.h>
#include <Session.h>
#include <Packet_v1.h>
#include <Client.h>

QSettings       settings(QSettings::IniFormat,QSettings::UserScope, "LiveJamming", "live-jamming");

MainWindow::MainWindow(Proxy* proxy) :
    QMainWindow(),
    ui(new Ui::MainWindow),
    proxy(proxy)
{
    ui->setupUi(this);
    setVisible(true);
    ui->mainToolBar->hide();
    qRegisterMetaType<authEventsType>("MainWindow::authEventsType");
    qRegisterMetaType<chanEventsType>("MainWindow::chanEventsType");

    redButton.setPixmap(QIcon(":/images/ledred-48x48.png").pixmap(statusIconSize));
    greenButton.setPixmap(QIcon(":/images/ledgreen-48x48.png").pixmap(statusIconSize));
    statusBar()->addPermanentWidget(&redButton);

    isConnected = false;
    connect(QCoreApplication::instance(), SIGNAL(aboutToQuit()), this, SLOT(on_actionDisconnect_triggered()));

    connect(proxy, SIGNAL(sAuthResponse(MainWindow::authEventsType)), this, SLOT(authEvents(MainWindow::authEventsType)), Qt::QueuedConnection);
    connect(proxy, SIGNAL(sChanResponse(MainWindow::chanEventsType, const Packet_v1_Channel*)), this, SLOT(chanEvents(MainWindow::chanEventsType, const Packet_v1_Channel*)),Qt::QueuedConnection);
    connect(proxy, SIGNAL(joinOk(QString)), this, SLOT(createRoom(QString)), Qt::QueuedConnection);

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
        //ui->statusBar->showMessage(connected ? "Connected" : "Disconnected");
        ui->statusBar->removeWidget(connected ? &redButton : &greenButton);
        ui->statusBar->addPermanentWidget(connected ? &greenButton : &redButton);
        connected ? greenButton.show() : redButton.show();
        ui->menuFile->removeAction(connected ? ui->actionConnect : ui->actionDisconnect);
        ui->menuFile->insertAction(ui->actionCreate_account,
                                   connected ? ui->actionDisconnect : ui->actionConnect);
        Q_FOREACH(QAction* action, ui->menuChans->actions())
            action->setEnabled(connected);
    }

    if (connected == false)
        Q_FOREACH(const QString& channel, channels.keys())
            leaveChannel(channel);
}

void MainWindow::authEvents(authEventsType event)
{
    switch (event) {
    case OK:
        setConnected(true);
        break ;
    case DISCONNECTED:
        QMessageBox::critical(this, "Connection Error", "You've been disconnected");
        setConnected(false);
        break ;
    case BADAUTH:
        QMessageBox::critical(this, "Authentication error", "Wrong login/password");
        break ;
    case TIMEOUT:
        QMessageBox::critical(this, "Authentication error", "Connection timeout");
        break ;
    case DUPPLICATE:
        QMessageBox::critical(this, "Authentication error", "Already logged in");
        break ;
    }
}

void    MainWindow::chanEvents(chanEventsType event, const Packet_v1_Channel* packet)
{
  char const * channelName = proxy->channel()->getChannelName(packet->getChannelId());

    switch(event) {
    case JOIN_OK:
        proxy->channelIdToName[packet->getChannelId()] = proxy->channel()->getChannelName(packet->getChannelId());
        proxy->clientIdToName[proxy->_session->getSessionId()] = settings.value("user/login").toString();
        joinChannel(channelName);
        break;
    case LEAVE_OK:
        leaveChannel(proxy->channelIdToName[packet->getChannelId()]);
        proxy->channelIdToName.remove(packet->getChannelId());
        break;
    case JOINED:
        qDebug() << "FROM PROXY" << packet->getClientLogin() << "joined" << proxy->channel()->getChannelName(packet->getChannelId());
        proxy->clientIdToName[packet->getClientSessionId()] = packet->getClientLogin();
        addClientToChannel(proxy->channelIdToName[packet->getChannelId()], packet->getClientLogin());
        break;
    case LEAVED:
        qDebug() << packet->getClientLogin() << "leaved" << proxy->channelIdToName[packet->getChannelId()];
        removeClientFromChannel(proxy->channelIdToName[packet->getChannelId()], packet->getClientLogin());
        break;
    case MESSAGE_RECV:
        assert(proxy->clientIdToName.contains(packet->getClientSessionId()));
        addMessage(proxy->channelIdToName[packet->getChannelId()], proxy->clientIdToName[packet->getClientSessionId()], QString::fromUtf8(packet->getMessage()));
        break;
    case ALREADYINCHAN:
        QMessageBox::information(this, "Error", "Already in chan");
    }
}

void    MainWindow::joinChannel(const QString &name)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(name));
    ui->channelList->addTopLevelItem(item);
    ui->channelList->setCurrentItem(item);
    item->setExpanded(true);

    ConversationSet* convSet = new ConversationSet(ui->stackedWidget);
    connect(convSet, SIGNAL(msgSend(const QString&)), this, SLOT(sendMessage(const QString&)));

    ui->stackedWidget->addWidget(convSet);
    ui->stackedWidget->setCurrentWidget(convSet);
    currentChannel = name;

    channels[name] = (UiChannel){item, convSet};
    addClientToChannel(name, settings.value("user/login").toString());
}

void    MainWindow::leaveChannel(const QString &name)
{
    ui->stackedWidget->removeWidget(channels[name].convSet);
    delete channels[name].convSet;
    delete channels[name].item;

    channels.remove(name);
}

void    MainWindow::addClientToChannel(const QString &channel, const QString &client)
{
    Q_ASSERT(channels.find(channel) != channels.end());
    QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(client));
    channels[channel].item->addChild(item);
    if (client != settings.value("user/login").toString())
        channels[channel].convSet->addEvent(client + " has joined");

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
    channels[channel].convSet->addEvent(client + " has leaved");

    clients.remove(client);
}

void    MainWindow::addMessage(const QString &channel, const QString &client, const QString &msg)
{
    Q_ASSERT(channels.contains(channel));
    Q_ASSERT(clients.contains(client));

    channels.value(channel).convSet->addMessage(client, msg);
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
                       settings.value("user/login").toString().toStdString(),
                       settings.value("user/password").toString().toStdString(),
                       settings.value("server/ip").toString().toStdString(),
                       settings.value("server/port").toInt());
	   }
       }
    }
}


void MainWindow::on_actionDisconnect_triggered()
{
    if (isConnected == true)
      {
	proxy->client->Disconnect();
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

    int retv = dial.exec();
    if ( retv == QDialog::Accepted && !dialui.nameLineEdit->text().isEmpty()) {
        proxy->channel()->Send_Join(proxy->session()->_session, dialui.nameLineEdit->text().toUtf8().data());
    }
}

void MainWindow::on_channelList_customContextMenuRequested(QPoint pos)
{
    int nbSelectedItems = ui->channelList->selectedItems().size();

    if (nbSelectedItems == 1) {
        if (ui->channelList->indexAt(pos).isValid()) {
            QString item = ui->channelList->itemAt(pos)->text(0);
            if (channels.contains(item)) { //it's a channel
                QAction leave("leave", 0);
                QAction* action = QMenu::exec(QList<QAction*>() << &leave, ui->channelList->mapToGlobal(pos));
                if (action == &leave)
                    proxy->channel()->Send_Leave(proxy->session()->_session, proxy->channelNameToId(item));
            }
        }
    }

    else {
        QList<QTreeWidgetItem*> selectedItems = ui->channelList->selectedItems();
        foreach (QTreeWidgetItem* item , selectedItems) { //checking there is no chan in the selected rows
            if (channels.contains(item->text(0)))
                return ;
        }
        QAction invite("Invite", 0);
        QAction* action = QMenu::exec(QList<QAction*>() << &invite, ui->channelList->mapToGlobal(pos));
        if (action == &invite)
            ;//proxy->channel()->Se
    }
}

void MainWindow::on_channelList_clicked(const QModelIndex& index)
{
    currentChannel = ui->channelList->itemFromIndex(index)->text(0);
    if (channels.contains(currentChannel))
        ui->stackedWidget->setCurrentWidget(channels[currentChannel].convSet);
}

void MainWindow::on_actionCreate_room_triggered()
{
    bool    ok;
    QString name = QInputDialog::getText(this, "Room name", "Enter room name", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
        proxy->room()->Send_Join(proxy->session()->_session, name.toUtf8().data());
    }
}

void MainWindow::sendMessage(const QString& msg)
{
        proxy->channel()->Send_Message(proxy->session()->_session, msg.toUtf8().data(), proxy->channelNameToId(currentChannel));
}

void MainWindow::createRoom(const QString &name)
{
    RoomDialog* room =
    new RoomDialog(this, proxy, name);
    room->joined(settings.value("user/login").toString());
}

void MainWindow::on_actionList_channels_triggered()
{
    //ChannelSearch* cs =
    new ChannelSearch(proxy, this);
}
