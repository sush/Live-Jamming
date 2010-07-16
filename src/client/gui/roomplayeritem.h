#ifndef ROOMPLAYERITEM_H
#define ROOMPLAYERITEM_H

#include <QWidget>

namespace Ui {
    class RoomPlayerItem;
}

class RoomPlayerItem : public QWidget {
    Q_OBJECT
public:
    RoomPlayerItem(QWidget *parent = 0);
    ~RoomPlayerItem();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RoomPlayerItem *ui;
};

#endif // ROOMPLAYERITEM_H
