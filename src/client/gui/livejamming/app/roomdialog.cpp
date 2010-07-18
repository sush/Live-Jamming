#include "roomdialog.h"
#include "ui_roomdialog.h"
#include "proxy.h"
#include "roomplayeritem.h"
#include <QSettings>

#include <Component_Room.h>
#include <Component_Session.h>
#include <qdebug.h>

RoomDialog::RoomDialog(QWidget *parent, Proxy* proxy, const QString& name) :
    QDialog(parent),
    ui(new Ui::RoomDialog),
    proxy(proxy)
{
    ui->setupUi(this);
    ui->playersVBox->setAlignment(ui->invite, Qt::AlignHCenter);
    setWindowTitle("Room - " + name);

    joined(QSettings().value("user/login").toString());
    connect(proxy, SIGNAL(joined(QString)), this, SLOT(joined(QString)), Qt::QueuedConnection);
    connect(proxy, SIGNAL(leaved(QString)), this, SLOT(leaved(QString)), Qt::QueuedConnection);
    connect(proxy, SIGNAL(messageRecv(QString,QString)), ui->convSet, SLOT(addMessage(const QString&, const QString&)), Qt::QueuedConnection);

    connect(ui->convSet, SIGNAL(msgSend(const QString&)), this, SLOT(sendMessage(const QString&)));

    setAttribute(Qt::WA_DeleteOnClose);
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

void    RoomDialog::closeEvent(QCloseEvent*)
{
    proxy->room()->Send_Leave(proxy->session()->_session, proxy->roomid);
}

void    RoomDialog::joined(QString client)
{
    RoomPlayerItem* item = new RoomPlayerItem(this, client, QString("Paris, France"));
    ui->playersVBox->insertWidget(0, item);
    players.insert(client, (UiRoomPlayer){item});
}

void    RoomDialog::leaved(QString client)
{
    Q_ASSERT(players.contains(client));

    delete players.value(client).item;
    players.remove(client);
}

void    RoomDialog::sendMessage(const QString &msg)
{
    qDebug() << "ROOMID = " <<  proxy->roomid;
    proxy->room()->Send_Message(proxy->session()->_session, msg.toUtf8().data(), proxy->roomid);
}
