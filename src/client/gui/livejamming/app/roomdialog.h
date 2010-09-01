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

    void closeEvent(QCloseEvent*);
    QMap<QString, UiRoomPlayer> players;

public slots:
    void    joined(const QString& client);
    void    leaved(const QString& client);

private slots:
    void on_startButton_clicked(bool checked);
    void    sendMessage(const QString&login);
    void    startedStopedJam(bool started);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RoomDialog *ui;
    Proxy*  proxy;
};

#endif // ROOMDIALOG_H
