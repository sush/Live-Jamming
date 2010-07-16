#include "roomplayeritem.h"
#include "ui_roomplayeritem.h"

RoomPlayerItem::RoomPlayerItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomPlayerItem)
{
    ui->setupUi(this);
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
