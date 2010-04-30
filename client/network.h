#ifndef NETWORK_H
#define NETWORK_H

#include <QTcpSocket>

class Network
{
public:
    Network();
    bool    connect(QString const& login, QString const& password);
    bool    isConnected();

private:
    QTcpSocket sock;
    bool    connected;
    //voir QProperty
};

#endif // NETWORK_H
