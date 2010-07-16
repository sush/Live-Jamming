#ifndef ROOMDIALOG_H
#define ROOMDIALOG_H

#include <QDialog>
#include <QMap>

namespace Ui {
    class RoomDialog;
}

class QString;
class Proxy;
class RoomPlayerItem;

struct UiRoomPlayer
{
    RoomPlayerItem* item;
};

class RoomDialog : public QDialog {
    Q_OBJECT
public:
    RoomDialog(QWidget *parent, Proxy* proxy, const QString& name);
    ~RoomDialog();

    QMap<QString, UiRoomPlayer> players;

public slots:
    void    joined(QString client);
    void    leaved(QString client);
    void    messageRecv(QString client, QString msg);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RoomDialog *ui;
};

#endif // ROOMDIALOG_H
