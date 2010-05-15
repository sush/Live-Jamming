#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindow;

#include <QMainWindow>
#include <ClientManager.h>
#include <QModelIndex>
#include <parameters.h>

namespace Ui {
    class MainWindow;
}

typedef std::pair<Packet_v1 const *, Session *>		queueElem;
typedef std::queue<queueElem>				l_eventQueue;

extern	l_eventQueue					eventQueue;

class Parameters;
class Session;
class Packet;

class MainWindow : public QMainWindow, public ClientManager
{
    Q_OBJECT
public:
    MainWindow(boost::asio::io_service &, boost::threadpool::pool &,
               boost::asio::ip::udp::socket &, boost::asio::ip::udp::endpoint &);
    ~MainWindow();
    static void gui_init(int argc, char* argv[]);
    static int run();
    void    authresponse_ok(Packet_v1 const*, Session* );
    void    authresponse_nok_badauth(Packet_v1 const*, Session* );

    void    chan_msg_receveid(Packet_v1 const*, Session*);

    void    add_chan(QString const& name);

    typedef void    (MainWindow::*pMethod)(Packet_v1 const*, Session*);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow  *ui;
    Parameters      params;
    bool            isConnected;

    void    populate_chans();
    void    populate_friends();

signals:
    void    toto();

private slots:
    void on_FriendsList_activated(QModelIndex index);
    void on_ChansList_activated(QModelIndex index);
    void on_actionNew_Chan_triggered();
    void on_actionAdd_Friend_triggered();
    void on_actionCreate_account_triggered();
    void on_actionNew_Room_triggered();
    void on_actionQuit_triggered();
    void on_actionPreferences_triggered();
    void on_actionConnect_triggered();
    void connected();
  void poll();
};

#endif // MAINWINDOW_H
