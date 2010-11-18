#ifndef ROOMDIALOG_H
#define ROOMDIALOG_H

#include <QDialog>
#include <QMap>
#include <QSignalMapper>

#include <QDebug>
#include <QTimer>

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

    virtual void closeEvent(QCloseEvent* e);
    virtual void hideEvent(QHideEvent *e);
    QMap<QString, UiRoomPlayer> players;

public slots:
    void    joined(QString client);
    void    leaved(const QString& client);

private slots:
    void on_pushButton_clicked();
    void on_startButton_clicked(bool checked);
    void    sendMessage(const QString&login);
    void    startedStopedJam(bool started);
    void    userKicked(QString user);
    void    youvebeenKicked();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RoomDialog *ui;
    Proxy*  proxy;
};

class Watcher : public QObject
{
    Q_OBJECT
public:
    Watcher(RoomDialog* parent = 0);
    ~Watcher() {qDebug() << "watcher destroyed";}
    void    pendingJoin(const QString& login);
    void    stopTrying();
private:
    QTimer  t;
    QString login;
    RoomDialog*   room;
    bool    pending;
    QSignalMapper mapper;
};

#endif // ROOMDIALOG_H
