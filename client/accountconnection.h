#ifndef ACCOUNTCONNECTION_H
#define ACCOUNTCONNECTION_H

#include <QDialog>
#include <QAbstractSocket>

namespace Ui {
    class AccountConnection;
}

class AccountConnection : public QDialog {
    Q_OBJECT
public:
    AccountConnection(QWidget *parent = 0);
    ~AccountConnection();
    static bool    run(QString& login, QString& password);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AccountConnection *ui;

private slots:
};

#endif // ACCOUNTCONNECTION_H
