#ifndef ACCOUNTCONNECTION_H
#define ACCOUNTCONNECTION_H

#include <QDialog>
#include <QAbstractSocket>

namespace Ui {
    class AccountConnection;
}
class QTcpSocket;

class AccountConnection : public QDialog {
    Q_OBJECT
public:
    AccountConnection(QWidget *parent = 0);
    ~AccountConnection();
    QList<QString> get_infos();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AccountConnection *ui;
    QTcpSocket* tcpSocket;

private slots:
    void on_buttonBox_accepted();
    void on_socket_error(QAbstractSocket::SocketError);
    void receiving_account_info();
};

#endif // ACCOUNTCONNECTION_H
