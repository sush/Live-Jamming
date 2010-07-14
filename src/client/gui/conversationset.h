#ifndef CONVERSATIONSET_H
#define CONVERSATIONSET_H

#include <QWidget>
#include <ui_conversationset.h>

class ConversationSet : public QWidget, public Ui::ConversationSet
{
Q_OBJECT
public:
    explicit ConversationSet(QWidget *parent = 0);

signals:

public slots:

};

#endif // CONVERSATIONSET_H
