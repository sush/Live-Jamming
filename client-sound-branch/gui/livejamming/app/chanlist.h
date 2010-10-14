#ifndef CHANLIST_H
#define CHANLIST_H

#include <QDialog>

namespace Ui {
    class chanList;
}

class chanList : public QDialog {
    Q_OBJECT
public:
    chanList(QWidget *parent = 0);
    ~chanList();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::chanList *ui;
};

#endif // CHANLIST_H
