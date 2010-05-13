#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ClientManager.h"
#include "event.h"

namespace Ui {
    class MainWindow;
}

class Parameters;
class Session;
class Packet;

class MainWindow : public QMainWindow, public ClientManager {
    Q_OBJECT
public:
    MainWindow(boost::asio::io_service &, boost::threadpool::pool &,
               boost::asio::ip::udp::socket &, boost::asio::ip::udp::endpoint &);
    ~MainWindow();
    static int run(int argc, char* argv[]);
    void    auth_session_ok(Packet_v1 const*, Session* );
    void    auth_session_pasok(Packet_v1 const*, Session*);

    typedef void    (MainWindow::*pMethod)(Packet_v1 const*, Session*);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow  *ui;
    Parameters      *params;
    Event           event;
    bool            isConnected;

    void    populate_chans();
    void    populate_friends();

private slots:
    void on_actionNew_Chan_triggered();
    void on_actionAdd_Friend_triggered();
    void on_actionCreate_account_triggered();
    void on_actionNew_Room_triggered();
    void on_actionQuit_triggered();
    void on_actionPreferences_triggered();
    void on_actionConnect_triggered();
    void connected();
};

#endif // MAINWINDOW_H
