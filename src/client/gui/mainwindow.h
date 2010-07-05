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

class Parameters;
class Session;
class Packet;
class QTreeWidgetItem;

class ChanManager
{
private:
    QList<Chan> chanList;
};

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
    ChanManager     chan;

    void    populate_chans();
    void    populate_friends();

signals:
    void    sConnectionAnswer(bool success);
    void    sDisconnected();

private slots:
    void on_ChansList_itemActivated(QTreeWidgetItem* item, int column);
    void on_actionDisconnect_triggered();
    void on_actionNew_Chan_triggered();
    void on_actionAdd_Friend_triggered();
    void on_actionCreate_account_triggered();
    void on_actionNew_Room_triggered();
    void on_actionQuit_triggered();
    void on_actionPreferences_triggered();
    void on_actionConnect_triggered();
    void setConnected(bool connected);
    void connectionAnswer(bool success);
};


#endif // MAINWINDOW_H
