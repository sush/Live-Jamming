#ifndef PROXY_H
#define PROXY_H

#include <mainwindow.h>
#include <QObject>
#include <QMap>
#include <QString>

class Client;
class Packet_v1_Session;
class Packet_v1_Channel;
class Session;

class Proxy : public QObject, public ClientManager
{
    Q_OBJECT
public :
        Proxy(Client* client, boost::asio::io_service& service, boost::threadpool::pool& pool,
              boost::asio::ip::udp::socket& socket, boost::asio::ip::udp::endpoint& endpoint);

void    authResponse(Packet_v1 const*, Session*);
void    chanResponse(Packet_v1 const*, Session*);
void    roomResponse(Packet_v1 const*, Session*);

// New interface not used yet (be aware of new connections / disconnections
 void	Connect(Session *){}
 void	Disconnect(Session *){}
   //////////////////////////////////////
void    disconnect();

QMap<QString, field_t>    channelNameToId;
QMap<QString, field_t>    clientNameToId;
const char* channelIdToName(field_t);

typedef void    (Proxy::*pMethod)(Packet_v1 const*, Session*);

Component_Session*    session() {return _session; }
Component_Channel*    channel() {return _channel; }
Component_Room*       room() {return _room; }

Client *              client;

signals:
void    sAuthResponse(MainWindow::authEventsType);
void    sChanResponse(MainWindow::chanEventsType, const Packet_v1_Channel*);
void    joinOk(QString);
void    joined(QString);
void    leaved(QString);
void    messageRecv(QString, QString);
};

#endif // PROXY_H
