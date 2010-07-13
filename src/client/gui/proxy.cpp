#include <Protocol_Session.h>
#include <Protocol_Channel.h>
#include <Component_Channel.h>
#include <Component_Session.h>
#include <proxy.h>

Proxy::Proxy(MainWindow *mainwin, boost::asio::io_service &service,
             boost::threadpool::pool &pool, boost::asio::ip::udp::socket &socket, boost::asio::ip::udp::endpoint &endpoint)
                 : ClientManager(service, pool, socket, endpoint)
{
    connect(this, SIGNAL(sAuthResponse(MainWindow::authEventsType)), mainwin, SLOT(authEvents(MainWindow::authEventsType)), Qt::QueuedConnection);
    connect(this, SIGNAL(sChanResponse(MainWindow::chanEventsType, const Packet_v1_Channel*)), mainwin, SLOT(chanEvents(MainWindow::chanEventsType, const Packet_v1_Channel*)),Qt::QueuedConnection);
}

void    Proxy::authResponse(Packet_v1 const* packet, Session* session)
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



void    Proxy::chanResponse(Packet_v1 const* packet_, Session* session)
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

void    Proxy::disconnect()
{
    emit sAuthResponse(MainWindow::DISCONNECTED);
}
