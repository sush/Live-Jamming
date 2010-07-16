#ifndef ACCOUNTCONNECTION_H
#define ACCOUNTCONNECTION_H

#include <QDialog>
#include <QSettings>

namespace Ui {
    class AccountConnection;
}

class AccountConnection : public QDialog
{
    Q_OBJECT
public:
    AccountConnection(QWidget *parent = 0);
    ~AccountConnection();
    static bool    run(QWidget* parent, const QString& login ,const QString& password,const QString& serverIp, const QString& serverPort);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AccountConnection *ui;

private slots:
};

#endif // ACCOUNTCONNECTION_H
