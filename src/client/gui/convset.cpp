#include "convset.h"
#include "ui_convset.h"

convSet::convSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::convSet)
{
    ui->setupUi(this);
}

convSet::~convSet()
{
    delete ui;
}

void convSet::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
