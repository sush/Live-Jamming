#ifndef CONVSET_H
#define CONVSET_H

#include <QWidget>

namespace Ui {
    class convSet;
}

class convSet : public QWidget {
    Q_OBJECT
public:
    convSet(QWidget *parent = 0);
    ~convSet();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::convSet *ui;
};

#endif // CONVSET_H
