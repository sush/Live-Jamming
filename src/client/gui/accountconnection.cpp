#include "accountconnection.h"
#include "ui_accountconnection.h"

#include <qdebug.h>

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

bool  AccountConnection::run(QWidget* parent, QString& login, QString & password, QString& serverIp, QString& serverPort)
{
    AccountConnection ac(parent);
    ac.ui->loginLineEdit->setText(login);
    ac.ui->passwordLineEdit->setText(password);
    ac.ui->serverIpLineEdit->setText(serverIp);
    ac.ui->serverPortLineEdit->setText(serverPort);
    //pas présent dans le ui
    connect(ac.ui->buttonBox, SIGNAL(accepted()), &ac, SLOT(accept()));
    connect(ac.ui->buttonBox, SIGNAL(rejected()), &ac, SLOT(reject()));
    if (ac.exec() != QDialog::Accepted)
       return false;
    login = ac.ui->loginLineEdit->text();
    password = ac.ui->passwordLineEdit->text();
    serverIp = ac.ui->serverIpLineEdit->text();
    serverPort = ac.ui->serverPortLineEdit->text();
    return true;
}
