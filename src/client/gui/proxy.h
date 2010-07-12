#ifndef PROXY_H
#define PROXY_H

#include <mainwindow.h>
#include <QObject>

class Packet_v1_Session;
class Packet_v1_Channel;
class Session;

class Proxy : public QObject, public ClientManager
{
    Q_OBJECT
public :
        Proxy(MainWindow* mainwin, boost::asio::io_service& service, boost::threadpool::pool& pool,
              boost::asio::ip::udp::socket& socket, boost::asio::ip::udp::endpoint& endpoint);

void    authResponse(Packet_v1 const*, Session*);
void    chanResponse(Packet_v1 const*, Session*);

typedef void    (Proxy::*pMethod)(Packet_v1 const*, Session*);

Component_Session*    session() {return _session; }
Component_Channel*    channel() {return _channel; }

signals:
void    sAuthResponse(MainWindow::authEventsType);
void    sChanResponse(MainWindow::chanEventsType, const Packet_v1_Channel*);
};

#endif // PROXY_H
