#include "network.h"

Network::Network()
{
}

bool    Network::connect(QString const& login, QString const& password)
{
    qDebug() << login << ':' << password;
    connected = true;
    return connected;
}

bool    Network::isConnected()
{
    return false;
}
