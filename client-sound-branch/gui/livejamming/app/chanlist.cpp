#include "chanlist.h"
#include "ui_chanlist.h"
#include <QPushButton>

chanList::chanList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chanList)
{
    ui->setupUi(this);
}

chanList::~chanList()
{
    delete ui;
}

void chanList::changeEvent(QEvent *e)
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
