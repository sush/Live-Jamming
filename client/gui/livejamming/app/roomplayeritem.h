#ifndef ROOMPLAYERITEM_H
#define ROOMPLAYERITEM_H

#include <QWidget>

namespace Ui {
    class RoomPlayerItem;
}

class RoomPlayerItem : public QWidget {
    Q_OBJECT
public:
    RoomPlayerItem(QWidget *parent, const QString& name, const QString& location);
    ~RoomPlayerItem();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RoomPlayerItem *ui;
};

#endif // ROOMPLAYERITEM_H
