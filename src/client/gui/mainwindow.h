#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ClientManager.h"
#include "event.h"

namespace Ui {
    class MainWindow;
}

class Network;
class Parameters;
class Session;

class MainWindow : public QMainWindow, public ClientManager {
    Q_OBJECT
public:
    MainWindow(boost::asio::io_service &, boost::threadpool::pool &,
               boost::asio::ip::udp::socket &, boost::asio::ip::udp::endpoint &);
    ~MainWindow();
    int main(boost::asio::io_service& service, boost::threadpool::pool& pool,
             boost::asio::ip::udp::socket& socket, boost::asio::ip::udp::endpoint& endpoint);

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
