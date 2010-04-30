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

bool  AccountConnection::run(QString& login, QString & password)
{
    AccountConnection ac;
    bool retv = ac.exec();
    if (retv != 0) //FIXME: return value to be tested
       return false;
    login = ac.ui->loginLineEdit->text();
    password = ac.ui->passwordLineEdit->text();
    return true;
}
