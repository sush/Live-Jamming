#ifndef CONVSET_H
#define CONVSET_H

#include "QWidget"
#include "QPlainTextEdit"
#include "QLineEdit"

class   convSet : public QWidget
{
public:
    convSet(QWidget* parent) : QWidget(parent),
        plainText(new QPlainTextEdit(this)),
        lineEdit(new QLineEdit(this))
    {
    }
    QPlainTextEdit* plainText;
    QLineEdit*  lineEdit;
};

#endif // CONVSET_H
