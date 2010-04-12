#include "accountconnection.h"
#include "ui_accountconnection.h"
#include "accountinformations.h"

#include <yaml.h>
#include <fstream>
#include <QTemporaryFile>
#include <QTcpSocket>
#include <QPushButton>
#include <QMessageBox>
#include <QObject>

AccountConnection::AccountConnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountConnection)
{
    ui->setupUi(this);
}

AccountConnection::~AccountConnection()
{
    delete ui;
}

void AccountConnection::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void AccountConnection::on_buttonBox_accepted()
{
    ui->loginLineEdit->setEnabled(false);
    ui->passwordLineEdit->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiving_account_info()));
    //connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(on_socket_error(QAbstractSocket::SocketError)));

    tcpSocket->connectToHost("127.0.0.1", 6666);

    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "login" << YAML::Value << ui->loginLineEdit->text().toStdString();
    out << YAML::Key << "password" << YAML::Value << ui->passwordLineEdit->text().toStdString();
    out << YAML::EndMap;

    tcpSocket->write(out.c_str());

}

void AccountConnection::receiving_account_info()
{
    std::istringstream stream;
    stream.str(tcpSocket->readAll().data());
    YAML::Parser parser(stream);

    AccountInformations AccInf;
    YAML::Node doc;
    parser.GetNextDocument(doc);

    std::list<QString> list;
    doc["infos"] >> AccInf.infos;
    //YAML::Node = doc["friends"];
    qDebug() << AccInf.infos.c_str();
}

void AccountConnection::on_socket_error(QAbstractSocket::SocketError)
{
    QMessageBox::critical(0, tr("Unable to join the server"), tcpSocket->errorString());
    exit(0);
    this->close();
}
