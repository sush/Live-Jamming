#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindow;

#include <QMainWindow>
#include <ClientManager.h>
#include <QModelIndex>
#include <parameters.h>

#include <chan.h>

namespace Ui {
    class MainWindow;
}

class Proxy;
class Packet_v1_Channel;


class MainWindow : public QMainWindow
{
    Q_OBJECT
    //Q_ENUMS(authEventsType);

public:
    MainWindow();
    ~MainWindow();
    static void gui_init(int argc, char* argv[]);
    static int run();
    void    setProxy(Proxy* proxy_);

    enum authEventsType{OK, BADAUTH, DUPPLICATE, DISCONNECTED};
    enum chanEventsType{JOIN_OK, ALREADYINCHAN, LEAVE_OK, JOINED, LEAVED, MESSAGE_RECV, LISTED};

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow  *ui;
    Parameters      params;
    Proxy*          proxy;
    bool            isConnected;

public slots:
    void authEvents(MainWindow::authEventsType event);
    void chanEvents(MainWindow::chanEventsType event, const Packet_v1_Channel*);
    void chanJoinOk(const char*);

private slots:
    void on_actionCreate_Channel_triggered();
    void on_actionDisconnect_triggered();
    void on_actionAdd_Friend_triggered();
    void on_actionCreate_account_triggered();
    void on_actionQuit_triggered();
    void on_actionPreferences_triggered();
    void on_actionConnect_triggered();
    void setConnected(bool);

};

#endif // MAINWINDOW_H
