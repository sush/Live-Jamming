#include "roomdialog.h"
#include "ui_roomdialog.h"
#include "proxy.h"
#include "roomplayeritem.h"
#include "ui_kickdialog.h"
#include <QSettings>
#include <QMessageBox>
#include <QListWidget>
#include <QDebug>
#include <QCloseEvent>

#include <Component_Room.h>
#include <Component_Session.h>

#include <boost/thread/mutex.hpp>

boost::mutex    roomLock;
extern QSettings settings;

RoomDialog::RoomDialog(QWidget *parent, Proxy* proxy, const QString& name) :
    QDialog(parent),
    ui(new Ui::RoomDialog),
    proxy(proxy)
{
    ui->setupUi(this);
    ui->playersVBox->setAlignment(ui->invite, Qt::AlignHCenter);
    setWindowTitle(name + " - Room");

    connect(proxy, SIGNAL(joined(QString)), this, SLOT(joined(QString)), Qt::QueuedConnection);
    connect(proxy, SIGNAL(leaved(QString)), this, SLOT(leaved(QString)), Qt::QueuedConnection);
    connect(proxy, SIGNAL(messageRecv(QString,QString)), ui->convSet, SLOT(addMessage(const QString&, const QString&)), Qt::QueuedConnection);
    connect(proxy, SIGNAL(startedStopedJam(bool)), this, SLOT(startedStopedJam(bool)), Qt::QueuedConnection);

    connect(ui->convSet, SIGNAL(msgSend(const QString&)), this, SLOT(sendMessage(const QString&)));

    connect(proxy, SIGNAL(kicked(QString)), this, SLOT(userKicked(QString)), Qt::QueuedConnection);
    connect(proxy, SIGNAL(userKicked()), this, SLOT(youvebeenKicked()),Qt::QueuedConnection);

    setAttribute(Qt::WA_DeleteOnClose);
    show();
}

RoomDialog::~RoomDialog()
{
    delete ui;
}

void RoomDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void    RoomDialog::closeEvent(QCloseEvent* e)
{
    proxy->room()->Send_Leave(proxy->roomid);
    e->accept();
}

void    RoomDialog::hideEvent(QHideEvent *)
{
    close();
}

void    RoomDialog::joined(QString client)
{
    boost::mutex::scoped_lock(roomLock);
    qDebug() << "\nXXXXXX IN ROOMDIALOG:" << client << "has joined the room\n";
    RoomPlayerItem* item = new RoomPlayerItem(this, client, QString("Paris, France"));
    ui->playersVBox->insertWidget(players.size(), item);
    players.insert(client, (UiRoomPlayer){item});
}

void    RoomDialog::leaved(const QString& client)
{
    qDebug() << "clients list";
    foreach(QString player, players.keys())
        qDebug() << player;

    qDebug() << "client leaving" << client;
    Q_ASSERT(players.contains(client));

    delete players.value(client).item;
    players.remove(client);
}

void    RoomDialog::sendMessage(const QString &msg)
{
    proxy->room()->Send_Message(msg.toUtf8().data(), proxy->roomid);
}

void RoomDialog::on_startButton_clicked(bool play)
{
    if (play)
        proxy->room()->Send_Start_Jam(proxy->roomid);
    else
        proxy->room()->Send_Stop_Jam(proxy->roomid);
    ui->startButton->setText("Pending...");
    ui->startButton->setIcon(QIcon());
}

void    RoomDialog::startedStopedJam(bool started)
{
    ui->startButton->setText(started ? "stop" : "start");
    ui->startButton->setIcon(QIcon(started ? ":/images/player_stop-30x30.png" : ":/images/player_play-30x30.png"));
}

void RoomDialog::on_pushButton_clicked()
{
    QDialog box(this);
    Ui::KickDialog* kickdial = new Ui::KickDialog;
    kickdial->setupUi(&box);
    QList<QString>  playerList = players.keys();
    playerList.removeAll(settings.value("user/login").toString());
    kickdial->listWidget->addItems(playerList);
    if (box.exec() == QDialog::Accepted) {
        foreach(QListWidgetItem* elem,  kickdial->listWidget->selectedItems()) {
            proxy->room()->Send_Kick(proxy->clientIdToName.keys(elem->text())[0], proxy->roomid);
            qDebug() << "Kicking player:" << elem->text();
        }
    }
}

void    RoomDialog::userKicked(QString user)
{
    ui->convSet->addEvent(user + " have been kicked");
    leaved(user);
}

void    RoomDialog::youvebeenKicked()
{
    QMessageBox::information(this, "Kickage", "You've been kicked by admin");
    delete this;
}
