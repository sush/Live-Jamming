#ifndef ROOMDIALOG_H
#define ROOMDIALOG_H

#include <QDialog>

namespace Ui {
    class RoomDialog;
}

class RoomDialog : public QDialog {
    Q_OBJECT
public:
    RoomDialog(QWidget *parent = 0);
    ~RoomDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RoomDialog *ui;
};

#endif // ROOMDIALOG_H
