#include "roomplayeritem.h"
#include "ui_roomplayeritem.h"

RoomPlayerItem::RoomPlayerItem(QWidget *parent, const QString &name, const QString &location) :
    QWidget(parent),
    ui(new Ui::RoomPlayerItem)
{
    ui->setupUi(this);
    ui->label->setText("<b>" + name + "</b>  " + "<i>" + location + "</i>");

    ui->speaker->setPixmap(QIcon(":/images/kmixdocked-48x48.png").pixmap(30));
}

RoomPlayerItem::~RoomPlayerItem()
{
    delete ui;
}

void RoomPlayerItem::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
