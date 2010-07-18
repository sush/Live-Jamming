#include <Protocol_Session.h>
#include <Protocol_Channel.h>
#include <Protocol_Room.h>
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
    }
    emit sAuthResponse(type);
}

void    Proxy::chanResponse(Packet_v1 const* packet_, Session*)
{
    const Packet_v1_Channel* packet = static_cast<const Packet_v1_Channel*>(packet_);
    MainWindow::chanEventsType type;
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
        type = MainWindow::LISTED; break;
    }
    emit sChanResponse(type, packet);
}

void    Proxy::roomResponse(const Packet_v1 *packet_, Session *)
{
    const Packet_v1_Room* packet = static_cast<const Packet_v1_Room*>(packet_);

    switch (packet->getRequestId())
    {
    case ROOM_JOIN_OK:
        emit joinOk(packet->getRoomName()); break;
    case ROOM_JOINED:
        emit joined(packet->getClientLogin()); break;
    case ROOM_LEAVED:
        emit leaved(packet->getClientLogin()); break;
    case ROOM_MESSAGE_RECV:
        emit messageRecv(packet->getClientLogin(), packet->getMessage());

    }
}

void    Proxy::disconnect()
{
  //    emit sAuthResponse(MainWindow::DISCONNECTED);
}

const char*    Proxy::channelIdToName(field_t id)
{
    Q_ASSERT(_channel->getAllChannel().size() != 0);

    return _channel->getAllChannel().find(id)->second->getName();
}


