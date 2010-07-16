#ifndef CONVERSATIONSET_H
#define CONVERSATIONSET_H

#include <QWidget>
#include <ui_conversationset.h>

#include <qdebug.h>

class ConversationSet : public QWidget, public Ui::ConversationSet
{
Q_OBJECT
public:
    explicit ConversationSet(QWidget *parent = 0);
    ~ConversationSet() { qDebug() << "DESTROYED"; }
signals:

public slots:

};

#endif // CONVERSATIONSET_H
