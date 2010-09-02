#include <Protocol_Session.h>
#include <Protocol_Channel.h>
#include <Protocol_Room.h>
#include <string>
#include <Component_Channel.h>
#include <Component_Session.h>
#include <Component_Room.h>
#include <proxy.h>

#include <qdebug.h>

Proxy::Proxy(Client* client, boost::asio::io_service &service,
             boost::threadpool::pool &pool, boost::asio::ip::udp::socket &socket, boost::asio::ip::udp::endpoint &endpoint) :
                    ClientManager(service, pool, socket, endpoint),
                    client(client)
{
}


void    Proxy::authResponse(Packet_v1 const* packet, Session*)
{
    field_t event = static_cast< Packet_v1_Session const*>(packet)->getRequestId();
    MainWindow::authEventsType type;
    bool    handled = true;

    switch (event)
    {
    case SESSION_AUTHRESPONSE_OK:
        type = MainWindow::OK; break;
    case SESSION_AUTHRESPONSE_NOK_BADAUTH:
        type = MainWindow::BADAUTH; break;
    case SESSION_AUTHRESPONSE_NOK_DUPLICATE:
        type = MainWindow::DUPPLICATE; break;
    case SESSION_DISCONNECTED:
        type = MainWindow::DISCONNECTED; break;
    default:
        handled = false;
    }

    if (handled == true)
        emit sAuthResponse(type);
}

QString op(const std::string& str)
{
    return QString::fromStdString(str);
}

void    Proxy::chanResponse(Packet_v1 const* packet_, Session*)
{
    const Packet_v1_Channel* packet = static_cast<const Packet_v1_Channel*>(packet_);
    MainWindow::chanEventsType type;
    bool    handled = true;

    switch (packet->getRequestId())
    {
    case CHANNEL_JOIN_OK:
        type = MainWindow::JOIN_OK; break;
    case CHANNEL_JOIN_NOK_ALREADYINCHAN:
        type = MainWindow::ALREADYINCHAN; break;
    case CHANNEL_LEAVE_OK:
        type = MainWindow::LEAVE_OK; break;
    case CHANNEL_JOINED:
        type = MainWindow::JOINED; break;
    case CHANNEL_LEAVED:
        type = MainWindow::LEAVED; break;
    case CHANNEL_MESSAGE_RECV:
        type = MainWindow::MESSAGE_RECV; break;
    case CHANNEL_LISTED:
        type = MainWindow::LISTED;
        static QStringList sl;
        qDebug() << "PROXY RECVED LIST ! !";
//        sl = std::vector<std::string>();
//        transform(packet->getChannelList().begin(), packet->getChannelList().end(),
//                  std::vector<std::string>(packet->getChannelList().size()).begin(), op);
        foreach(std::string str, packet->getChannelList())
            sl << QString::fromStdString(str);
        emit channelsListed(sl);
        return ;
    default:
        handled = false;
    }

    if (handled)
        emit sChanResponse(type, packet);
}

void    Proxy::roomResponse(const Packet_v1 *packet_, Session *)
{
    const Packet_v1_Room* packet = static_cast<const Packet_v1_Room*>(packet_);

    switch (packet->getRequestId())
    {
    case ROOM_JOIN_OK:
        roomid = packet->getRoomId();
        emit joinOk(packet->getRoomName()); break;
    case ROOM_JOINED:
        emit joined(packet->getClientLogin()); break;
    case ROOM_LEAVED:
        emit leaved(packet->getClientLogin()); break;
    case ROOM_MESSAGE_RECV:
        qDebug() << "ROOM MSG RECEIVED:" << packet->getMessage();
        emit messageRecv(packet->getClientLogin(), packet->getMessage()); break;
    case ROOM_STARTED_JAM:
        emit startedStopedJam(true); break;
    case ROOM_STOPED_JAM:
        emit startedStopedJam(false); break;
    }
}

void    Proxy::disconnect()
{
  //    emit sAuthResponse(MainWindow::DISCONNECTED);
}

unsigned int    Proxy::channelNameToId(const QString &name)
{
    QMapIterator<unsigned int, QString> it(channelIdToName);
    while (it.hasNext()) {
        it.next();
        if (it.value() == name)
            return it.key();
    }
    bool chan_not_found_in_list = true;
    assert(chan_not_found_in_list);
}
