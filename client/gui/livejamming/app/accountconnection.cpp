#include "accountconnection.h"
#include "ui_accountconnection.h"

#include <qdebug.h>

extern QSettings settings;

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

bool  AccountConnection::run(MainWindow* parent, const QString& login, const QString & password,const QString& serverIp, const QString& serverPort)
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
    /*parent->*/settings.setValue("user/login", ac.ui->loginLineEdit->text());
    /*parent->*/settings.setValue("user/password",ac.ui->passwordLineEdit->text());
    /*parent->*/settings.setValue("server/ip", ac.ui->serverIpLineEdit->text());
    /*parent->*/settings.setValue("server/port", ac.ui->serverPortLineEdit->text());
    return true;
}
