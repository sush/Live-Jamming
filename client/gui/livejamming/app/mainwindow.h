#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindow;

#include <QMainWindow>
#include <ClientManager.h>
//#include <Component_Channel.h>
#include <QMap>
#include <QSettings>
#include <QLabel>

#include <accountconnection.h>

namespace Ui {
    class MainWindow;
}

class Proxy;
class Packet_v1_Channel;
class QModelIndex;
class QTreeWidgetItem;
class ConversationSet;

struct UiChannel
{
    QTreeWidgetItem* item;
    ConversationSet*    convSet;
};

struct UiClient
{
    QTreeWidgetItem* item;
};

const int statusIconSize = 20;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class AccountConnection;

public:
    MainWindow(Proxy* proxy);
    ~MainWindow();
    static void gui_init(int argc, char* argv[]);
    static int run();

    enum authEventsType{OK, BADAUTH, DUPPLICATE, TIMEOUT, DISCONNECTED};
    enum chanEventsType{JOIN_OK, ALREADYINCHAN, LEAVE_OK, JOINED, LEAVED, MESSAGE_RECV, LISTED};

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow  *ui;
    Proxy*          proxy;
    bool            isConnected;
    QLabel          redButton;
    QLabel          greenButton;
    QLabel          infos;
    QString         currentChannel;
    QMap<QString, UiChannel>   channels;
    QMap<QString, UiClient>    clients;

private:
    void joinChannel(const QString& name);
    void leaveChannel(const QString& name);
    void addClientToChannel(const QString& channel, const QString& login);
    void removeClientFromChannel(const QString& channel, const QString& login);
    void addMessage(const QString& channel, const QString& client, const QString& msg);
    void setConnected(bool);

public slots:
    void authEvents(MainWindow::authEventsType event);
    void chanEvents(MainWindow::chanEventsType event, const Packet_v1_Channel*);

private slots:
    void on_actionList_channels_triggered();
    void on_actionCreate_room_triggered();
    void on_channelList_clicked(const QModelIndex& index);
    void on_channelList_customContextMenuRequested(QPoint pos);
    void on_actionCreate_Channel_triggered();
    void on_actionDisconnect_triggered();
    void on_actionAdd_Friend_triggered();
    void on_actionCreate_account_triggered();
    void on_actionQuit_triggered();
    void on_actionPreferences_triggered();
    void on_actionConnect_triggered();
    void sendMessage(const QString&);
    void createRoom(const QString& name);
};

#endif // MAINWINDOW_H
